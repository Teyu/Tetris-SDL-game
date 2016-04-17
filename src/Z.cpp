#include "Z.h"

void CZ::Reset()
{

	int x = static_cast<int>(m_fXPos);
	int y = static_cast<int>(m_fYPos);

	for (int i = 0; i < 4; i++)
	{
		m_Pos[i].Load("Data/GreenBlock.bmp"); 
	} 

	m_fXPos = 10*m_Pos[0].GetRect().w/2;
	m_fYPos = 0.0f;
	m_fXPos -= m_Pos[0].GetRect().w;
	x = m_fXPos;

	m_Pos[0].SetPos(x,y); 
	x += m_Pos[0].GetRect().w;
	m_Pos[1].SetPos(x,y); 
	y += m_Pos[0].GetRect().w;
	m_Pos[2].SetPos(x,y); 
	x += m_Pos[0].GetRect().w;
	m_Pos[3].SetPos(x,y);

	if (m_bIsFallingFast)
		FastDown(false);
}
