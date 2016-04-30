#include "Form.h"

/****************************************************************************************************************************************************
constructor
*/

CForm::CForm() : m_fXPos(0.0f), m_fYPos(0.0f),
    m_RotPoint(0), m_size(0),
    m_screenW(0), m_screenH(0),
    m_bIsFallingFast(false), m_FastFallingPoints(0),
    m_fAutoMove(0.0f),
    m_fTempo(0.0f), m_fFastTempo(0.0f)
{
}

/****************************************************************************************************************************************************
destructor
*/

CForm::~CForm()
{
}

/****************************************************************************************************************************************************
initialising
*/

void CForm::Init(float fTempo)
{
	//set start position
    ResetPos();

	m_size = m_Pos[0].GetRect().h;
	m_screenW = 10* m_size;
	m_screenH = 20*m_size;
	m_fTempo = fTempo;

	m_bIsFallingFast = false;
	m_FastFallingPoints = 0;
    m_fAutoMove = 0.0f;
	m_fFastTempo = 600.0f;

	m_RotPoint = 1; 
}

/****************************************************************************************************************************************************
set start position (to be overwritten)
*/

void CForm::ResetPos()
{
}

/****************************************************************************************************************************************************
render form
*/

void CForm::Render()
{
	for (int i=0; i < 4; i++)
	{
		m_Pos[i].Render();
	}

	g_pField->Render(); 
}

/****************************************************************************************************************************************************
form is falling down one block with defined speed.
returns true if it actually fell down and false if the end of fall is reached.	
*/

bool CForm::Fall()
{
	float dy = m_fTempo * g_pTimer->GetElapsed();
	Move(0.0f, dy);

    bool ReturnValue = true;

    //verify if the bottom screen border is reached
	for (int i = 0; i < 4; i++)
	{
        if ((m_Pos[i].GetRect().y == m_screenH)
            || (g_pField->IsBlock(m_Pos[i].GetRect().x, m_Pos[i].GetRect().y)))
		{
			ReturnValue = false;
			break;
		}
	}

	if (ReturnValue == false)
	{	
		for (int i = 0; i < 4; i++)
		{
			//reset position if the form didn't fall. 
            //necessary so that one is still able to move a form horizontally that reached its end of fall
			m_Pos[i].SetPos(m_Pos[i].GetRect().x, m_Pos[i].GetRect().y - m_size);

			g_pField->IncludeForm(m_Pos[i]);
		}
		if (m_FastFallingPoints != 0)
			g_pPlayer->IncreasePoints(m_FastFallingPoints -1); 

		return false; 
	}

	return true;
}

/****************************************************************************************************************************************************
rotate form if possible
*/

void CForm::Rotate()
{
    float x_newP[4];
    float y_newP[4];

    for (int i = 0; i < 4; i++)
    {
        //x-axis and y-axis values of m_Pos if m_RotPoint was (0,0)
        float x_RotP = m_Pos[i].GetRect().x - m_Pos[m_RotPoint].GetRect().x;
        float y_RotP = m_Pos[i].GetRect().y - m_Pos[m_RotPoint].GetRect().y;

        //90°-rotation of (x_RotP, y_RotP) at m_RotPoint
        float x = x_RotP;
        float y = y_RotP;
        x_RotP = - y;
        y_RotP = x;

        x_newP[i] = m_Pos[m_RotPoint].GetRect().x + x_RotP;
        y_newP[i] = m_Pos[m_RotPoint].GetRect().y + y_RotP;

    //verify if there is enough space to rotate

        if ((x_newP[i] >= m_screenW) || (x_newP[i] < 0.0f)) return;
        if ((y_newP[i] >= m_screenH) || (y_newP[i] < 0.0f)) return;
        if (g_pField->IsBlock(x_newP[i], y_newP[i])) return;
    }

    //update member variables:
    m_fXPos += (x_newP[0] - m_Pos[0].GetRect().x);
    m_fYPos += (y_newP[0] - m_Pos[0].GetRect().y);

    for (int i = 0; i < 4; i++)
    {
        m_Pos[i].SetPos(x_newP[i], y_newP[i]);
    }
}

/****************************************************************************************************************************************************
form is falling down at a higher speed if regarding button is pressed
*/

void CForm::FastDown(bool bStart)
{
	if ((bStart) && (!m_bIsFallingFast))
	{
		float tmp = m_fTempo;
		m_fTempo = m_fFastTempo;
		m_fFastTempo = tmp;
		m_bIsFallingFast = true;
	}

	if ((!bStart) && (m_bIsFallingFast))
	{
		float tmp = m_fFastTempo;
		m_fFastTempo = m_fTempo;
		m_fTempo = tmp; 
		m_bIsFallingFast = false;
	}
}

/****************************************************************************************************************************************************
move form one size of a block to the left or right depending on which button has been pressed
*/

void CForm::Move(int Dir, bool KeyHold)
{
	int puffer = 80;
	float AutoSpeed = 500.0f;

	//verify if there is enough space
	for (int i = 0; i < 4; i++)
	{
		if (((m_Pos[i].GetRect().x >= (m_screenW - m_size)) && (Dir == SDLK_RIGHT)) 
			|| ((m_Pos[i].GetRect().x <= 0) && (Dir == SDLK_LEFT))) //horizontal screenborder?
		{
			return;
		}
		if ((m_Pos[i].GetRect().y/m_size - 1 >= 0) && (m_Pos[i].GetRect().x + 1 <= m_screenW) && //vertical screenborder (right)?
            (((g_pField->IsBlock(m_Pos[i].GetRect().x+ m_size, m_Pos[i].GetRect().y)) && (Dir == SDLK_RIGHT)) //is there a block in the way (right)?
			|| ((m_Pos[i].GetRect().x/m_size - 1 >= 0) && (m_Pos[i].GetRect().y/m_size - 1 >= 0) && //vertical screenborder (left)?
            (g_pField->IsBlock(m_Pos[i].GetRect().x- m_size, m_Pos[i].GetRect().y)) && (Dir == SDLK_LEFT)))) //is there a block in the way (left)?
		{
			return;
		}
	}

	float dx = 0.0f; 

	if (Dir == SDLK_RIGHT)
	{
		if (KeyHold)
		{
            if (m_fAutoMove > puffer)
			{
				dx =  AutoSpeed * g_pTimer->GetElapsed();
			}else
			{
                m_fAutoMove += 300.0f * g_pTimer->GetElapsed();
			}
		} else if (!KeyHold)
		{
			dx = static_cast<float>(m_size);
            m_fAutoMove = 0.0f;
		}
	} else if (Dir == SDLK_LEFT)
	{
		if (KeyHold)
		{
            if (m_fAutoMove > puffer)
			{
				dx = - AutoSpeed * g_pTimer->GetElapsed();
			}else
			{
                m_fAutoMove += 300.0f * g_pTimer->GetElapsed();
			}
		} else if (!KeyHold)
		{
			dx = - static_cast<float>(m_size);
            m_fAutoMove = 0.0f;
		}
	}

	Move(dx, 0.0f);
}

/****************************************************************************************************************************************************
move form by vector (dx, dy)
*/

void CForm::Move(float fdx, float fdy)
{
	m_fXPos += fdx;
	m_fYPos += fdy;
	//blockwise movement
	int x = static_cast<int>(m_fXPos) - static_cast<int>(m_fXPos)%m_size;
	int y = static_cast<int>(m_fYPos) - static_cast<int>(m_fYPos)%m_size;

	SDL_Rect tmp = m_Pos[0].GetRect();
	for (int i = 0; i < 4; i++)
	{
		x += m_Pos[i].GetRect().x - tmp.x;
		y += m_Pos[i].GetRect().y - tmp.y;
		tmp = m_Pos[i].GetRect();

		m_Pos[i].SetPos( x, y); 

		if (((m_bIsFallingFast) && (i==0)) && ((m_Pos[i].GetRect().y - tmp.y)/m_size != 0)) 
		{
			m_FastFallingPoints += (m_Pos[i].GetRect().y - tmp.y)/m_size;
		} else if (!m_bIsFallingFast)
		{
			m_FastFallingPoints = 0;
		}
	}
}
