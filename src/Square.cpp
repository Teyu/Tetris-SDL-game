#include "Square.h"

CSquare::~CSquare()
{
}

void CSquare::ResetPos()
{
	for (int i = 0; i < 4; i++)
	{
        m_Pos[i].Load("data/OrangeBlock.bmp");
	} 

    m_fXPos = 10*m_Pos[0].GetRect().w/2;
	m_fXPos -= m_Pos[0].GetRect().w;

    m_fYPos = m_Pos[0].GetRect().h;

    float x = m_fXPos;
    float y = m_fYPos;
    for (int i = 0; i < 4; x += m_Pos[i].GetRect().w, i++)
	{
		m_Pos[i].SetPos(x,y); 
		if (i == 1)
		{
            y += m_Pos[i].GetRect().h;
            x -= 2*m_Pos[i].GetRect().w;
        }
	}

	if (m_bIsFallingFast)
		FastDown(false);
}
