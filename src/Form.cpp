#include "Form.h"

/****************************************************************************************************************************************************
constructor
*/

CForm::CForm() :
    m_fXPos(0.0f), m_fYPos(0.0f),

    m_size(0),

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

void CForm::Init(float fFallingSpeed, unsigned int startX, unsigned int startY)
{
    m_fFallingSpeed = fFallingSpeed;
    m_bIsAlive = true;

    loadBlockImage();
    m_size = m_Blocks[0].GetRect().h;

    setPos(static_cast<float>(startX)*m_size, static_cast<float>(startY)*m_size);
    m_fXPos = m_Blocks[0].GetRect().x;
    m_fYPos = m_Blocks[0].GetRect().y;
}

/****************************************************************************************************************************************************
render form
*/

void CForm::Render()
{
    for (size_t i=0; i < 4; i++)
	{
        m_Blocks[i].Render();
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
