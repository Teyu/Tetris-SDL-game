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

//the different kind of Tetris-forms:

class CBar: public CForm
{
public:
    void setStartPos()
    {
        float x = m_fieldW/2 - 2*m_size, y = m_size;
        for (int i = 0; i < 4; x += m_size, i++)
        {
            m_Blocks[i].SetPos(x,y);
        }
    }

    void loadBlockImage()
    {
        for (int i = 0; i < 4; i++)
        {
            m_Blocks[i].Load("data/RedBlock.bmp");
        }
    }
    ~CBar(){}
};

class CJ: public CForm
{
public:
    void setStartPos()
    {
        float x = m_fieldW/2, y = m_size;
        for (int i = 0; i < 4; i == 2 ? x -= m_size : y += m_size, i++)
        {
            m_Blocks[i].SetPos(x,y);
        }
    }
    void loadBlockImage()
    {
        for (int i = 0; i < 4; i++)
        {
            m_Blocks[i].Load("data/VioletBlock.bmp");
        }
    }
    ~CJ(){}
};

class CL: public CForm
{
public:
    void setStartPos()
    {
        float x = m_fieldW/2 - m_size, y = m_size;
        for (int i = 0; i < 4; i == 2 ? x += m_size : y += m_size, i++)
        {
            m_Blocks[i].SetPos(x,y);
        }
    }
    void loadBlockImage()
    {
        for (int i = 0; i < 4; i++)
        {
            m_Blocks[i].Load("data/BlueBlock.bmp");
        }
    }
    ~CL(){}
};

class CS: public CForm
{
public:
    void setStartPos()
    {
        float x = m_fieldW/2 - m_size, y = 2*m_size;
        for (int i = 0; i < 4; (i%2 == 0) ? x += m_size : y -= m_size, i++)
        {
            m_Blocks[i].SetPos(x,y);
        }
    }
    void loadBlockImage()
    {
        for (int i = 0; i < 4; i++)
        {
            m_Blocks[i].Load("data/YellowBlock.bmp");
        }
    }
    ~CS(){}
};

class CSquare: public CForm
{
public:
    void setStartPos()
    {
        float x = m_fieldW/2 - m_size, y = m_size;
        for (int i = 0; i < 4; x += m_size, i++)
        {
            m_Blocks[i].SetPos(x,y);
            if (i == 1)
            {
                y += m_Blocks[i].GetRect().h;
                x -= 2*m_Blocks[i].GetRect().w;
            }
        }
    }
    void loadBlockImage()
    {
        for (int i = 0; i < 4; i++)
        {
            m_Blocks[i].Load("data/OrangeBlock.bmp");
        }
    }
    void Rotate() {}
    ~CSquare(){}
};

class CT: public CForm
{
public:
    void setStartPos()
    {
        float x = m_fieldW/2 - m_size ,y = m_size;
        for (int i = 0; i < 4; x += m_size, i++)
        {
            m_Blocks[i].SetPos(x,y);
            if (i == 2)
            {
                x -= 2*m_Blocks[i].GetRect().w;
                y += m_Blocks[0].GetRect().h;
            }
        }
    }
    void loadBlockImage()
    {
        for (int i = 0; i < 4; i++)
        {
            m_Blocks[i].Load("data/TurkisBlock.bmp");
        }
    }
    ~CT(){}
};

class CZ: public CForm
{
public:
    void setStartPos()
    {
        float x = m_fieldW/2 - m_size, y = m_size;
        for (int i = 0; i < 4; (i%2 == 0) ? x += m_size : y += m_size, i++)
        {
            m_Blocks[i].SetPos(x,y);
        }
    }
    void loadBlockImage()
    {
        for (int i = 0; i < 4; i++)
        {
            m_Blocks[i].Load("data/GreenBlock.bmp");
        }
    }
    ~CZ(){}
};

#endif
