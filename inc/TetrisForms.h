#include "Form.h"

class CBar: public CForm
{
public:
    void setPos(float fx, float fy)
    {
        fx = fx - 2*m_size;
        for (int i = 0; i < 4; fx += m_size, i++)
        {
            m_Blocks[i].SetPos(fx,fy);
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
    void setPos(float fx, float fy)
    {
        for (int i = 0; i < 4; i == 2 ? fx -= m_size : fy += m_size, i++)
        {
            m_Blocks[i].SetPos(fx,fy);
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
    void setPos(float fx, float fy)
    {
        fx = fx - m_size;
        for (int i = 0; i < 4; i == 2 ? fx += m_size : fy += m_size, i++)
        {
            m_Blocks[i].SetPos(fx,fy);
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
    void setPos(float fx, float fy)
    {
        fx = fx - m_size;
        for (int i = 0; i < 4; (i%2 == 0) ? fx += m_size : fy -= m_size, i++)
        {
            m_Blocks[i].SetPos(fx,fy);
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
    void setPos(float fx, float fy)
    {
        fx = fx - m_size;
        for (int i = 0; i < 4; fx += m_size, i++)
        {
            m_Blocks[i].SetPos(fx,fy);
            if (i == 1)
            {
                fy += m_Blocks[i].GetRect().h;
                fx -= 2*m_Blocks[i].GetRect().w;
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
    void setPos(float fx, float fy)
    {
        fx = fx - m_size;
        for (int i = 0; i < 4; fx += m_size, i++)
        {
            m_Blocks[i].SetPos(fx,fy);
            if (i == 2)
            {
                fx -= 2*m_Blocks[i].GetRect().w;
                fy += m_Blocks[0].GetRect().h;
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
    void setPos(float fx, float fy)
    {
        fx = fx - m_size;
        for (int i = 0; i < 4; (i%2 == 0) ? fx += m_size : fy += m_size, i++)
        {
            m_Blocks[i].SetPos(fx,fy);
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
