#include "Form.h"

/****************************************************************************************************************************************************
Konstruktor
*/

CForm::CForm()
{
}

/****************************************************************************************************************************************************
Destruktor
*/

CForm::~CForm()
{
}

/****************************************************************************************************************************************************
Initialisiert die Startposition der Form.
Setzt InStartPos auf true (ALLGEMEIN)
*/

void CForm::Init(float fTempo)
{
	//Setze Position:
	Reset();

	//Initialisiere Membervariablen:	
	m_size = m_Pos[0].GetRect().h;
	m_screenW = 10* m_size;
	m_screenH = 20*m_size;
	m_fTempo = fTempo;

	//Initialisiere schnelles fallen:
	m_bIsFallingFast = false;
	m_FastFallingPoints = 0;
	m_AutoMove = 0.0f;
	m_fFastTempo = 600.0f;

	m_RotPoint = 1; 
}

/****************************************************************************************************************************************************
Legt Startposition fest. Diese wird von den abgeleiteten Klassen überschrieben (sieht je nach Form anders aus)
*/

void CForm::Reset()
{
}

/****************************************************************************************************************************************************
rendert die Form (ALLGEMEIN)
*/

void CForm::Render()
{
	for (int i=0; i < 4; i++)
	{
		m_Pos[i].Render();
	}

	g_pField->Render(); //Rendere auch die bereits liegenden Blöcke
}

/****************************************************************************************************************************************************
Die Form fällt in einer vorgegebenen Geschwindigkeit nach unten
Sie hört auf zu fallen, wenn die Höhe des Blockfeldes erreicht wurde
RÜCKGABEWERT: True, wenn die Form gefallen ist, false, wenn sie das Ende ihres Falls erreicht hat (ALLGEMEIN)
*/

bool CForm::Fall()
{
	
	//Bewege
	float dy = m_fTempo * g_pTimer->GetElapsed();
	Move(0.0f, dy);

	bool ReturnValue = true; //false, wenn das Ende des Falls erreicht wurde
	int h = m_size; //kürzere Schreibweise

	//Prüfe zunächst, ob die Form mit den Blöcken andockt:
	for (int i = 0; i < 4; i++)
	{
		if ((m_Pos[i].GetRect().y/h == (m_screenH/h))
			|| (g_pField->IsBlock(m_Pos[i].GetRect().x/h, (m_screenH - m_Pos[i].GetRect().y)/h - 1))) 
			//Befindet sich auf der gleichen Position ein Block oder ist das Ende des Bildschirms erreicht?
			//Beachte: Die Position ist immer ein Teiler von h!
		{
			ReturnValue = false;
			break;
		}
	}

	//Falls das Ende das Falls erreicht wurde, füge die Figur den liegenden Blöcken hinzu...
	if (ReturnValue == false)
	{	
		for (int i = 0; i < 4; i++)
		{
			//Setze die Form wieder einen Block hoch, sonst wird sie in die darunterliegenden Blöcke reingezeichnet.
			//Dies ist notwendig, damit Figur noch bewegt werden kann!!
			m_Pos[i].SetPos(m_Pos[i].GetRect().x, m_Pos[i].GetRect().y - m_size);

			g_pField->IncludeForm(m_Pos[i]);
		}
		//Der Spieler erhält Punkte für jeden Block, den er bis zum Boden durchgängig schnell fallen lies
		if (m_FastFallingPoints != 0)
			g_pPlayer->IncreasePoints(m_FastFallingPoints -1); //den letzten dabei nicht mitrechnen

		return false; //..und gebe false zurück
	}

	return true;
}

/****************************************************************************************************************************************************
Rotiert die Form, dabei muss abgefragt werden, ob genug Platz zum rotieren ist (ALLGEMEIN)
*/

void CForm::Rotate()
{
	int dx[4]; //Abstände der Blöcke zum Rotationspunkt
	int dy[4];

	//Prüfe zunächst, ob genug Platz zum rotieren ist: (sieht irgendwie hässlich aus...)
	for (int i = 0; i < 4; i++)
	{
		if ((m_Pos[i].GetRect().x == m_Pos[m_RotPoint].GetRect().x) && (m_Pos[i].GetRect().y < m_Pos[m_RotPoint].GetRect().y))
		{
			dx[i] = m_Pos[m_RotPoint].GetRect().y - m_Pos[i].GetRect().y;
			dy[i] = dx[i];
			if (((m_Pos[i].GetRect().x + dx[i] >= m_screenW) || (m_Pos[i].GetRect().x + dx[i] < 0) || (m_Pos[i].GetRect().y + dy[i] < 0)) //Bildschirmrand?
				|| (g_pField->IsBlock((m_Pos[i].GetRect().x + dx[i])/m_size, (m_screenH - (m_Pos[i].GetRect().y + dy[i]))/m_size))) //Block?
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
		//TEST:
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
		//ENDETEST
		else
		{
			dx[i] = 0;
			dy[i] = 0;
		}
	}
	
	//Rotation:
	for (int i = 0; i < 4; i++)
	{
		m_Pos[i].SetPos(m_Pos[i].GetRect().x + dx[i], m_Pos[i].GetRect().y + dy[i]);
	}

	//Position hat sich verändert: (ACHTUNG: ohne Konvertierung in float würde die Figur beim Rotieren nicht fallen!)
	m_fXPos += static_cast<float>(dx[0]);
	m_fYPos += static_cast<float>(dy[0]);
}

/****************************************************************************************************************************************************
lässt die Form schnell herunterfallen (ALLGEMEIN)
*/

void CForm::FastDown(bool bStart)
{
	if ((bStart) && (!m_bIsFallingFast))
	{
		float tmp = m_fTempo;
		m_fTempo = m_fFastTempo; //Tempo erhöhen
		m_fFastTempo = tmp;
		m_bIsFallingFast = true;
	}

	if ((!bStart) && (m_bIsFallingFast))
	{
		float tmp = m_fFastTempo;
		m_fFastTempo = m_fTempo;
		m_fTempo = tmp; //Tempo zurücksetzen, FastTempo hat sich die geschw. gemerkt
		m_bIsFallingFast = false;
	}
}

/****************************************************************************************************************************************************
Bewegt die Form um eine Blockgröße nach links oder Rechts, je nach Übergabewert (ALLGEMEIN)
*/

void CForm::Move(int Dir, bool KeyHold)
{
	int puffer = 80;
	float AutoSpeed = 500.0f;

	//Prüfe zunächst, ob genug Platz ist:
	for (int i = 0; i < 4; i++)
	{
		if (((m_Pos[i].GetRect().x >= (m_screenW - m_size)) && (Dir == SDLK_RIGHT)) 
			|| ((m_Pos[i].GetRect().x <= 0) && (Dir == SDLK_LEFT))) //Ist der horizontale Bildschirmrand erreicht?
		{
			return;
		}
		if ((m_Pos[i].GetRect().y/m_size - 1 >= 0) && (m_Pos[i].GetRect().x + 1 <= m_screenW) && //legale Übergabeparameter (vertikaler Bildschirmrand erreicht)?
			(((g_pField->IsBlock(m_Pos[i].GetRect().x/m_size + 1, (m_screenH - m_Pos[i].GetRect().y)/m_size - 1)) && (Dir == SDLK_RIGHT)) //Block im Weg?
			|| ((m_Pos[i].GetRect().x/m_size - 1 >= 0) && (m_Pos[i].GetRect().y/m_size - 1 >= 0) && //legale Übergabeparameter (vertikaler Bildschirmrand erreicht)?
			(g_pField->IsBlock(m_Pos[i].GetRect().x/m_size - 1, (m_screenH - m_Pos[i].GetRect().y)/m_size - 1)) && (Dir == SDLK_LEFT)))) //Block im Weg?
		{//Ist ein Block im Weg?
			return;
		}
	}

	//Lege die Richtung fest:
	float dx = 0.0f; //Wenn kein gültiger Wert übergeben wurde, bewegt sich die Form nicht

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

	//Bewege:
	Move(dx, 0.0f);
}

/****************************************************************************************************************************************************
Bewegt die Form um den Vektor (dx, dy)
(ALLGEMEIN)
*/

void CForm::Move(float fdx, float fdy)
{
	m_fXPos += fdx;
	m_fYPos += fdy;
	//Fallen Blockweise:
	//Beachte: Die Position soll ein Teiler von size sein, daher wird der überschüssige Teil abgeschnitten!
	int x = static_cast<int>(m_fXPos) - static_cast<int>(m_fXPos)%m_size;
	int y = static_cast<int>(m_fYPos) - static_cast<int>(m_fYPos)%m_size;

	SDL_Rect tmp = m_Pos[0].GetRect();
	for (int i = 0; i < 4; i++)
	{
		x += m_Pos[i].GetRect().x - tmp.x;
		y += m_Pos[i].GetRect().y - tmp.y;
		tmp = m_Pos[i].GetRect();

		m_Pos[i].SetPos( x, y); 

		//Falls der Block gerade am Schnellfallen ist, gibt das Punkte pro Blockdifferenz:
		if (((m_bIsFallingFast) && (i==0))/*Sonst wird  4 mal erhöht!*/ && ((m_Pos[i].GetRect().y - tmp.y)/m_size != 0)) 
		{
			m_FastFallingPoints += (m_Pos[i].GetRect().y - tmp.y)/m_size;
		} else if (!m_bIsFallingFast)
		{
			m_FastFallingPoints = 0;
		}
	}
}