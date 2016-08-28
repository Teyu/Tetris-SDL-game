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
    void Init(float fFallingSpeed, unsigned int startX, unsigned int startY);

    virtual void setPos(float fx, float fy) = 0;
    virtual void loadBlockImage() = 0;

    template<uint width, uint height>
    bool Fall(bool bFast, CField<width, height> * const field);
    template<uint width, uint height>
    void Rotate(CField<width, height> * const field);
    template<uint width, uint height>
    void Move(int Dir, bool bAutofire, CField<width, height> * const field);

    int GetSize() { return m_size;}
    int GetNumBlocksFastDown() {return m_fDistFastDown/m_size;}

    bool isAlive() {return m_bIsAlive;}

protected:
    float m_fXPos;
    float m_fYPos;

    unsigned int m_size;

    const int m_RotPoint;
    CSprite m_Blocks[4];

private:
    void Move(float dx, float dy);
    bool m_bIsAlive;

    float m_fFallingSpeed;
    float m_fDistFastDown;

    const float m_fFallingFastSpeed;
    const float m_fAutoMoveSpeed;
};

#include "../src/Form.inl"

#endif
