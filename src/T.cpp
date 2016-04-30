#include "T.h"

CT::~CT()
{
}

void CT::ResetPos()
{
	for (int i = 0; i < 4; i++)
	{
        m_Pos[i].Load("data/TurkisBlock.bmp");
	} 

	m_fXPos = 10*m_Pos[0].GetRect().w/2;
    m_fXPos -= m_Pos[0].GetRect().w;

    m_fYPos = m_Pos[0].GetRect().h;

    float x = m_fXPos;
    float y = m_fYPos;
    for (int i = 0; i < 4; x += m_Pos[i].GetRect().w, i++)
    {
        m_Pos[i].SetPos(x,y);
        if (i == 2)
        {
            x -= 2*m_Pos[i].GetRect().w;
            y += m_Pos[0].GetRect().h;
        }
    }

	if (m_bIsFallingFast)
		FastDown(false);
}
