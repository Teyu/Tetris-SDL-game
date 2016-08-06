#include "Form.h"

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
