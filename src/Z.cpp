#include "Z.h"

CZ::~CZ()
{
}

void CZ::Reset()
{
	for (int i = 0; i < 4; i++)
	{
        m_Pos[i].Load("data/GreenBlock.bmp");
	} 

    m_fXPos = 10*m_Pos[0].GetRect().w/2;
	m_fXPos -= m_Pos[0].GetRect().w;

    m_fYPos = m_Pos[0].GetRect().h;

    float x = m_fXPos;
    float y = m_fYPos;
    for (int i = 0; i < 4; (i%2 == 0) ? x += m_Pos[i].GetRect().w : y += m_Pos[i].GetRect().h, i++)
    {
        m_Pos[i].SetPos(x,y);
    }

	if (m_bIsFallingFast)
		FastDown(false);
}
