#include "Bar.h"

CBar::~CBar()
{
}

void CBar::Reset()
{
    for (int i = 0; i < 4; i++)
	{
        m_Pos[i].Load("data/RedBlock.bmp");
	} 

	//reset position
	//form starts on top central

    m_fXPos = 10*m_Pos[0].GetRect().w/2;
    m_fXPos -= 2*m_Pos[0].GetRect().w;

    m_fYPos = m_Pos[0].GetRect().h;

    float x = m_fXPos;
    float y = m_fYPos;
    for (int i = 0; i < 4; x += m_Pos[i].GetRect().w, i++)
    {
        m_Pos[i].SetPos(x,y);
	}

	//reset FastFall, otherwise new form could be falling fast 
	if (m_bIsFallingFast)
		FastDown(false);
}
