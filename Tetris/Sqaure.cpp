#include "Square.h"

void CSquare::Reset()
{


	int x = static_cast<int>(m_fXPos);
	int y = static_cast<int>(m_fYPos);

	for (int i = 0; i < 4; i++)
	{
		m_Pos[i].Load("Data/OrangeBlock.bmp"); 
	} 

	//Position zurücksetzen:
	//Die Form startet oben in der Mitte:
	m_fXPos = 10*m_Pos[0].GetRect().w/2;
	m_fYPos = 0.0f;
	m_fXPos -= m_Pos[0].GetRect().w;
	x = m_fXPos;

	for (int i = 0; i < 4; i++)
	{
		
		m_Pos[i].SetPos(x,y); 
		x += m_Pos[i].GetRect().w;
		if (i == 1)
		{
			y += m_Pos[i].GetRect().w;
			x -= 2*m_Pos[i].GetRect().w;
		}
	}

	//Nicht vergessen: FastFall zurücksetzen:
	if (m_bIsFallingFast)
		FastDown(false);
}