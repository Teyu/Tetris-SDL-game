/****************************************************************************************************************************************************
form is falling down one block with either normal (bFast = false) or fast (bFast = true) speed.
returns true if it succesfully fell down and false if it was not able to fall down.
*/

template<uint width, uint height>
bool CForm::Fall(float dy, CField<width, height> * const field)
{
    Move(0.0f, dy);

    for (size_t i = 0; i < 4; i++)
    {
        if ((m_Blocks[i].GetRect().y == height*m_size) || (field->IsBlock(m_Blocks[i].GetRect().x, m_Blocks[i].GetRect().y)))
        {
            Move(0.0f, -dy);

            for (int i = 0; i < 4; i++)
                field->IncludeBlock(m_Blocks[i]);

            m_bIsAlive = false;

            return false;
         }
    }

    return true;
}

template<uint width, uint height>
bool CForm::Fall(CField<width, height> * const field)
{
    float dy = m_fFallingSpeed * g_pTimer->GetElapsed();

    if (!Fall(dy, field))
        return false;

    m_fDistFastDown = 0;
    return true;
}

template<uint width, uint height>
bool CForm::FallFast(CField<width, height> * const field)
{
    float dy = m_fFallingFastSpeed * g_pTimer->GetElapsed();

    if (!Fall(dy, field))
        return false;

    m_fDistFastDown += dy;
    return true;
}

/****************************************************************************************************************************************************
rotate form if possible
*/

template<uint width, uint height>
void CForm::Rotate(CField<width, height> * const field)
{
    float x_newP[4];
    float y_newP[4];

    for (size_t i = 0; i < 4; i++)
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

        if (field->IsBlock(x_newP[i], y_newP[i])) return;

        //set back form if screenborders are blocking off the rotation, then reset loop

        if ((x_newP[i] >= width*m_size) || (x_newP[i] < 0.0f))
        {
            Move(static_cast<float>(x_newP[i] < 0.0f ? m_size : -m_size), 0.0f);
            i = - 1;  //ACHTUNG: ggf. endlosschleife -> TODO: assert in CField einfügen, dass dieses mindestens 4x4 groß sein muss
        }
        else if ((y_newP[i] >= height*m_size) || (y_newP[i] < 0.0f))
        {
            Move(0.0f,static_cast<float>(y_newP[i] < 0.0f ? m_size : -m_size));
            i = - 1;
        }
    }

    m_fXPos += (x_newP[0] - m_Blocks[0].GetRect().x);
    m_fYPos += (y_newP[0] - m_Blocks[0].GetRect().y);

    for (size_t i = 0; i < 4; i++)
    {
        m_Blocks[i].SetPos(x_newP[i], y_newP[i]);
    }
}

/****************************************************************************************************************************************************
move form one size of a block to the left or right depending on which button has been pressed
*/

template<uint width, uint height>
void CForm::Move(int Dir, bool bAutofire, CField<width, height> * const field)
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
    for (size_t i = 0; i < 4; i++)
    {
        if ((m_Blocks[i].GetRect().x == width*m_size) || (m_Blocks[i].GetRect().x < 0) ||
            (field->IsBlock(m_Blocks[i].GetRect().x, m_Blocks[i].GetRect().y)))
        {
            Move(-dx, 0.0f);
            return;
        }
    }
}
