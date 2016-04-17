#include "Form.h"

/****************************************************************************************************************************************************
constructor
*/

CForm::CForm()
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
	Reset();

	m_size = m_Pos[0].GetRect().h;
	m_screenW = 10* m_size;
	m_screenH = 20*m_size;
	m_fTempo = fTempo;

	m_bIsFallingFast = false;
	m_FastFallingPoints = 0;
	m_AutoMove = 0.0f;
	m_fFastTempo = 600.0f;

	m_RotPoint = 1; 
}

/****************************************************************************************************************************************************
set start position (to be overwritten)
*/

void CForm::Reset()
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
	int h = m_size; 

	//verify if the end of fall is reached
	for (int i = 0; i < 4; i++)
	{
		if ((m_Pos[i].GetRect().y/h == (m_screenH/h))
			|| (g_pField->IsBlock(m_Pos[i].GetRect().x/h, (m_screenH - m_Pos[i].GetRect().y)/h - 1)))
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
			//necessary so that one is still able to move a form that reached its end of fall
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
	//difference of the blocks to the rotation point
	int dx[4]; 
	int dy[4];

	//verify if there is enough space to rotate
	for (int i = 0; i < 4; i++)
	{
		if ((m_Pos[i].GetRect().x == m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y < m_Pos[m_RotPoint].GetRect().y))
		{
			dx[i] = m_Pos[m_RotPoint].GetRect().y - m_Pos[i].GetRect().y;
			dy[i] = dx[i];
			if (((m_Pos[i].GetRect().x + dx[i] >= m_screenW) || (m_Pos[i].GetRect().x + dx[i] < 0) || (m_Pos[i].GetRect().y + dy[i] < 0)) //end of screen?
				|| (g_pField->IsBlock((m_Pos[i].GetRect().x + dx[i])/m_size, (m_screenH - (m_Pos[i].GetRect().y + dy[i]))/m_size))) //block?
				return;
		} else if ((m_Pos[i].GetRect().x > m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y == m_Pos[m_RotPoint].GetRect().y))
		{
			dy[i] = m_Pos[i].GetRect().x - m_Pos[m_RotPoint].GetRect().x;
			dx[i] = -dy[i];
			if (((m_Pos[i].GetRect().x + dx[i] >= m_screenW) || (m_Pos[i].GetRect().x + dx[i] < 0) || (m_Pos[i].GetRect().y + dy[i] < 0))
				|| (g_pField->IsBlock((m_Pos[i].GetRect().x + dx[i])/m_size, (m_screenH - (m_Pos[i].GetRect().y + dy[i]))/m_size)))
				return;
		}else if ((m_Pos[i].GetRect().x == m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y > m_Pos[m_RotPoint].GetRect().y))
		{
			dx[i] = m_Pos[m_RotPoint].GetRect().y - m_Pos[i].GetRect().y;
			dy[i] = dx[i];
			if (((m_Pos[i].GetRect().x + dx[i] >= m_screenW) || (m_Pos[i].GetRect().x + dx[i] < 0) || (m_Pos[i].GetRect().y + dy[i] < 0))
				|| (g_pField->IsBlock((m_Pos[i].GetRect().x + dx[i])/m_size, (m_screenH - (m_Pos[i].GetRect().y + dy[i]))/m_size)))
				return;
		}else if ((m_Pos[i].GetRect().x < m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y == m_Pos[m_RotPoint].GetRect().y))
		{
			dx[i] = m_Pos[m_RotPoint].GetRect().x - m_Pos[i].GetRect().x;
			dy[i] = -dx[i];
			if (((m_Pos[i].GetRect().x + dx[i] >= m_screenW) || (m_Pos[i].GetRect().x + dx[i] < 0) || (m_Pos[i].GetRect().y+ dy[i] < 0))
				|| (g_pField->IsBlock((m_Pos[i].GetRect().x + dx[i])/m_size, (m_screenH - (m_Pos[i].GetRect().y + dy[i]))/m_size)))
				return;
		}else if ((m_Pos[i].GetRect().x > m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y < m_Pos[m_RotPoint].GetRect().y))
		{
			dx[i] = 0;
			dy[i] = (m_Pos[i].GetRect().x - m_Pos[m_RotPoint].GetRect().x) + (m_Pos[m_RotPoint].GetRect().y - m_Pos[i].GetRect().y);
		} else if ((m_Pos[i].GetRect().x > m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y > m_Pos[m_RotPoint].GetRect().y))
		{
			dy[i] = 0;
			dx[i] = (m_Pos[m_RotPoint].GetRect().x - m_Pos[i].GetRect().x) + (m_Pos[m_RotPoint].GetRect().y - m_Pos[i].GetRect().y);
		} else if ((m_Pos[i].GetRect().x < m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y > m_Pos[m_RotPoint].GetRect().y))
		{
			dx[i] = 0;
			dy[i] = (m_Pos[i].GetRect().x - m_Pos[m_RotPoint].GetRect().x) + (m_Pos[m_RotPoint].GetRect().y - m_Pos[i].GetRect().y);
		} else if ((m_Pos[i].GetRect().x < m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y < m_Pos[m_RotPoint].GetRect().y))
		{
			dy[i] = 0;
			dx[i] = (m_Pos[m_RotPoint].GetRect().x - m_Pos[i].GetRect().x) + (m_Pos[m_RotPoint].GetRect().y- m_Pos[i].GetRect().y);
		}
		else
		{
			dx[i] = 0;
			dy[i] = 0;
		}
	}
	
	//rotate
	for (int i = 0; i < 4; i++)
	{
		m_Pos[i].SetPos(m_Pos[i].GetRect().x + dx[i], m_Pos[i].GetRect().y + dy[i]);
	}

	//convertion to float otherwise the form wouldn't be falling while rotating
	m_fXPos += static_cast<float>(dx[0]);
	m_fYPos += static_cast<float>(dy[0]);
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
			(((g_pField->IsBlock(m_Pos[i].GetRect().x/m_size + 1, (m_screenH - m_Pos[i].GetRect().y)/m_size - 1)) && (Dir == SDLK_RIGHT)) //is there a block in the way (right)?
			|| ((m_Pos[i].GetRect().x/m_size - 1 >= 0) && (m_Pos[i].GetRect().y/m_size - 1 >= 0) && //vertical screenborder (left)?
			(g_pField->IsBlock(m_Pos[i].GetRect().x/m_size - 1, (m_screenH - m_Pos[i].GetRect().y)/m_size - 1)) && (Dir == SDLK_LEFT)))) //is there a block in the way (left)?
		{
			return;
		}
	}

	float dx = 0.0f; 

	if (Dir == SDLK_RIGHT)
	{
		if (KeyHold)
		{
			if (m_AutoMove > puffer)
			{
				dx =  AutoSpeed * g_pTimer->GetElapsed();
			}else
			{
				m_AutoMove += 300.0f * g_pTimer->GetElapsed();
			}
		} else if (!KeyHold)
		{
			dx = static_cast<float>(m_size);
			m_AutoMove = 0.0f;
		}
	} else if (Dir == SDLK_LEFT)
	{
		if (KeyHold)
		{
			if (m_AutoMove > puffer)
			{
				dx = - AutoSpeed * g_pTimer->GetElapsed();
			}else
			{
				m_AutoMove += 300.0f * g_pTimer->GetElapsed();
			}
		} else if (!KeyHold)
		{
			dx = - static_cast<float>(m_size);
			m_AutoMove = 0.0f;
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
