#include "Bar.h"

CBar::~CBar()
{
}

void CBar::Reset()
{
	int x = static_cast<int>(m_fXPos);
	int y = static_cast<int>(m_fYPos);

	for (int i = 0; i < 4; i++)
	{
        m_Pos[i].Load("data/RedBlock.bmp");
	} 

	//reset position
	//form starts on top central
	
	m_fXPos = 10*m_Pos[0].GetRect().w/2;
	m_fXPos -= 2*m_Pos[0].GetRect().w;
	x = m_fXPos;
    m_fYPos = m_Pos[0].GetRect().h;
    y = m_fYPos;

	for (int i = 0; i < 4; i++)
	{
		
		m_Pos[i].SetPos(x,y); 
		x += m_Pos[i].GetRect().w;
	}

	//reset FastFall, otherwise new form could be falling fast 
	if (m_bIsFallingFast)
		FastDown(false);
}
