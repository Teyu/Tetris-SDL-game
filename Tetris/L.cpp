#include "L.h"

void CL::Reset()
{
	
	int x = static_cast<int>(m_fXPos);
	int y = static_cast<int>(m_fYPos);

	for (int i = 0; i < 4; i++)
	{
		m_Pos[i].Load("Data/BlueBlock.bmp"); 
	} 
	m_fXPos = 10*m_Pos[0].GetRect().w/2;
	m_fYPos = 0.0f;
	m_fXPos -= m_Pos[0].GetRect().w;
	x = m_fXPos;

	for (int i = 0; i < 4; i++)
	{
		
		m_Pos[i].SetPos(x,y); 
		if (i == 2)
		{
			x += m_Pos[i].GetRect().w;
		} else
		{
			y += m_Pos[i].GetRect().w;
		}
	}

	if (m_bIsFallingFast)
		FastDown(false);
}
