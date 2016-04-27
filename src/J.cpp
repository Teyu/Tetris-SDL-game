#include "J.h"

CJ::~CJ()
{
}

void CJ::Reset()
{
	

	int x = static_cast<int>(m_fXPos);
	int y = static_cast<int>(m_fYPos);

	for (int i = 0; i < 4; i++)
	{
        m_Pos[i].Load("data/VioletBlock.bmp");
	} 

	m_fXPos = 10*m_Pos[0].GetRect().w/2;
    m_fYPos = m_Pos[0].GetRect().h;;
	m_fXPos -= m_Pos[0].GetRect().w;
	x = m_fXPos;
    y = m_fYPos;

	for (int i = 0; i < 4; i++)
	{
		
		m_Pos[i].SetPos(x,y); 
		if (i == 2)
		{
			x -= m_Pos[i].GetRect().w;
		} else
		{
			y += m_Pos[i].GetRect().w;
		}
	}

	if (m_bIsFallingFast)
		FastDown(false);
}
