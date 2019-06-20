#ifndef FORM_H
#define FORM_H

#include "Sprite.h"
#include "Timer.h"
#include "Field.h"
#include <array>

using namespace std;

enum Form {Bar, Square, L, J, Z, S, T};

class CForm
{
public:
    CForm();
    static CForm *create (Form shape);
    virtual ~CForm();

    void Render();
    void Init (float fFallingSpeed, unsigned int startX, unsigned int startY);

    virtual void setPos (float fx, float fy) = 0;
    virtual void loadBlockImage() = 0;

    template<uint32_t width, uint32_t height>
    bool Fall (CField<width, height> *const field);
    //TODO: use protected Fall function instead -> process speed of fall within a new class CControls which is part of CPlayer
    //-> replace CPlayer->ProcessFall with the appropiate CControl class
    template<uint32_t width, uint32_t height>
    bool FallFast (CField<width, height> *const field);
    template<uint32_t width, uint32_t height>
    void Rotate (CField<width, height> *const field);
    template<uint32_t width, uint32_t height>
    void Move (int Dir, bool bAutofire, CField<width, height> *const field); //TODO: make two functions out of this

    virtual Form GetType() = 0;
    int GetSize()
    {
        return m_size;
    }
    int GetNumBlocksFastDown()
    {
        return m_fDistFastDown / m_size;
    }

    bool isAlive()
    {
        return m_bIsAlive;
    }

protected:
    template<uint32_t width, uint32_t height>
    bool Fall (float dy, CField<width, height> *const field);

    float m_fXPos;
    float m_fYPos;

    unsigned int m_size;

    const int m_RotPoint;
    CSprite m_Blocks[4];

private:
    void Move (float dx, float dy);
    bool m_bIsAlive;

    float m_fFallingSpeed;
    float m_fDistFastDown;

    const float m_fFallingFastSpeed;
    const float m_fAutoMoveSpeed;
};

#include "../src/Form.inl"

#endif
