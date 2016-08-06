#ifndef FORM_H
#define FORM_H

#include "Sprite.h"
#include "Timer.h"
#include "Field.h"
#include <array>

using namespace std;

class CForm 
{
public:
    CForm();
    virtual ~CForm();
    void Render();
    void Init(float fFallingSpeed);

    virtual void setStartPos() = 0;
    virtual void loadBlockImage() = 0;

    bool Fall(bool bFast);
    virtual void Rotate();
    void Move(int Dir, bool bAutofire);
    int GetSize() { return m_size;}
    int GetNumFastDown() {return m_fDistFastDown/m_size;}

    bool isAlive() {return m_bIsAlive;}

protected:
    float m_fXPos;
    float m_fYPos;

    int m_size;
    int m_fieldW;
    int m_fieldH;

    const int m_RotPoint;
    CSprite m_Blocks[4];

private:
    void Move(float dx, float dy);
    bool m_bIsAlive;

    float m_fFallingSpeed;
    const float m_fFallingFastSpeed;
    float m_fDistFastDown;

    const float m_fAutoMoveSpeed;
};

#endif
