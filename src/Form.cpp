#include "Form.h"

/****************************************************************************************************************************************************
constructor
*/

CForm::CForm() :
    m_fXPos(0.0f), m_fYPos(0.0f),

    m_size(0), m_fieldW(0), m_fieldH(0),

    m_RotPoint(1),
    m_bIsAlive(false),

    m_fFallingSpeed(0.0f), m_fFallingFastSpeed(630.0f), m_fDistFastDown(0.0f),
    m_fAutoMoveSpeed(500.0f)

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

void CForm::Init(float fFallingSpeed)
{
    m_fFallingSpeed = fFallingSpeed;
    m_bIsAlive = true;

    loadBlockImage();
    m_size = m_Blocks[0].GetRect().h;
    m_fieldW = g_pField->GetFieldW()* m_size;
    m_fieldH = g_pField->GetFieldH()* m_size;

    setStartPos();
    m_fXPos = m_Blocks[0].GetRect().x;
    m_fYPos = m_Blocks[0].GetRect().y;
}

/****************************************************************************************************************************************************
render form
*/

void CForm::Render()
{
	for (int i=0; i < 4; i++)
	{
        m_Blocks[i].Render();
    }
}

/****************************************************************************************************************************************************
form is falling down one block with either normal (bFast = false) or fast (bFast = true) speed.
returns true if it succesfully fell down and false if it was not able to fall down.
*/

bool CForm::Fall(bool bFast)
{
    float dy = (bFast ? m_fFallingFastSpeed : m_fFallingSpeed) * g_pTimer->GetElapsed();
    Move(0.0f, dy);

	for (int i = 0; i < 4; i++)
	{
        if ((m_Blocks[i].GetRect().y == m_fieldH) || (g_pField->IsBlock(m_Blocks[i].GetRect().x, m_Blocks[i].GetRect().y)))
        {
            Move(0.0f, -dy);

            for (int i = 0; i < 4; i++)
                g_pField->IncludeBlock(m_Blocks[i]);

            m_bIsAlive = false;

            return false;
		}
    }

    if (m_bIsAlive)
        m_fDistFastDown = (bFast ? m_fDistFastDown + dy : 0);

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
        //x-axis and y-axis values of m_Blocks if m_RotPoint was (0,0)
        float x_RelRotP = m_Blocks[i].GetRect().x - m_Blocks[m_RotPoint].GetRect().x;
        float y_RelRotP = m_Blocks[i].GetRect().y - m_Blocks[m_RotPoint].GetRect().y;

        //90°-rotation of (x_RelRotP, y_RelRotP) at m_RotPoint
        float x = x_RelRotP;
        float y = y_RelRotP;
        x_RelRotP = - y;
        y_RelRotP = x;

        x_newP[i] = m_Blocks[m_RotPoint].GetRect().x + x_RelRotP;
        y_newP[i] = m_Blocks[m_RotPoint].GetRect().y + y_RelRotP;

        if (g_pField->IsBlock(x_newP[i], y_newP[i])) return;

        //set back form if screenborders are blocking off the rotation, then reset loop

        if ((x_newP[i] >= m_fieldW) || (x_newP[i] < 0.0f))
        {
            Move(float(x_newP[i] < 0.0f ? m_size : -m_size), 0.0f);
            i = - 1;
        }
        else if ((y_newP[i] >= m_fieldH) || (y_newP[i] < 0.0f))
        {
            Move(0.0f,float(y_newP[i] < 0.0f ? m_size : -m_size));
            i = - 1;
        }
    }

    m_fXPos += (x_newP[0] - m_Blocks[0].GetRect().x);
    m_fYPos += (y_newP[0] - m_Blocks[0].GetRect().y);

    for (int i = 0; i < 4; i++)
    {
        m_Blocks[i].SetPos(x_newP[i], y_newP[i]);
    }
}

/****************************************************************************************************************************************************
move form one size of a block to the left or right depending on which button has been pressed
*/

void CForm::Move(int Dir, bool bAutofire)
{
    if ((Dir != SDLK_RIGHT) && (Dir != SDLK_LEFT))
        return;

	float dx = 0.0f; 
    if (bAutofire)
    {
        dx = (float) (Dir == SDLK_RIGHT ? 1 : -1) * m_fAutoMoveSpeed * g_pTimer->GetElapsed();

    } else
    {
        dx = (float) (Dir == SDLK_RIGHT ? 1 : -1) * m_size;
    }

	Move(dx, 0.0f);

    //verify if there is enough space
    for (int i = 0; i < 4; i++)
    {
        if ((m_Blocks[i].GetRect().x == m_fieldW) || (m_Blocks[i].GetRect().x < 0) ||
                (g_pField->IsBlock(m_Blocks[i].GetRect().x, m_Blocks[i].GetRect().y)))
        {
            Move(-dx, 0.0f);
            return;
        }
    }
}

/****************************************************************************************************************************************************
move form blockwise by vector (dx, dy)
*/

void CForm::Move(float fdx, float fdy)
{
	m_fXPos += fdx;
	m_fYPos += fdy;

    //blockwise movement
    int dx = (static_cast<int>(m_fXPos) - static_cast<int>(m_fXPos)%m_size) - m_Blocks[0].GetRect().x;
    int dy = (static_cast<int>(m_fYPos) - static_cast<int>(m_fYPos)%m_size) - m_Blocks[0].GetRect().y;

    for (size_t i = 0; i < 4; i++ )
        m_Blocks[i].SetPos(m_Blocks[i].GetRect().x + dx, m_Blocks[i].GetRect().y + dy);
}
