
/****************************************************************************************************************************************************
update Player
*/

template<uint width, uint height>
void CPlayer::Update(CField<width,height> * const field)
{
    int Lines = field->GetDelLines();

    ProcessRotateForm(SDLK_UP, field);
    ProcessMoveForm(SDLK_RIGHT, SDLK_LEFT, field);
    ProcessFormFall(SDLK_DOWN, field);

    field->Update();
    m_DelLines += field->GetDelLines() - Lines;
}

/****************************************************************************************************************************************************
rotate Form if defined Key is pressed (no autofire)
*/

template<uint width, uint height>
void CPlayer::ProcessRotateForm(int Key_ID, CField<width, height> * const field)
{
    if ((g_pFramework->KeyDown(Key_ID)) && (!m_bKeyLock_Rotate) /*&& (m_TetrisForm != Square)*/)
    {
        m_pForm->Rotate(field);

        m_bKeyLock_Rotate = true;
    }
    else if (!g_pFramework->KeyDown(Key_ID))
    {
        m_bKeyLock_Rotate = false;
    }
}

/****************************************************************************************************************************************************
move Form to the left or right if defined key is pressed, unlock autofire if key is pressed longer than defined buffer time
*/

template<uint width, uint height>
void CPlayer::ProcessMoveForm(int Key_ID_Right, int Key_ID_Left, CField<width, height> * const field)
{
    ProcessMoveForm(Key_ID_Right, m_bKeyLock_MoveR, m_fAutoMoveCount_r, field);
    ProcessMoveForm(Key_ID_Left, m_bKeyLock_MoveL, m_fAutoMoveCount_l, field);
}

template<uint width, uint height>
void CPlayer::ProcessMoveForm(int Key_ID, bool &bKeyLockMove, float &fAutoMoveCount, CField<width, height> * const field)
{
    if (g_pFramework->KeyDown(Key_ID))
    {
        if (bKeyLockMove) //autofire
        {
            fAutoMoveCount += g_pTimer->GetElapsed();
            if (fAutoMoveCount > buffer)
                m_pForm->Move(Key_ID, true, field);
        } else
        {
            m_pForm->Move(Key_ID, false, field);
            bKeyLockMove = true;
        }
    } else
    {
        bKeyLockMove = false;
        fAutoMoveCount = 0.0f;
    }
}

/****************************************************************************************************************************************************
form is constantly falling down, let the form fall down faster if defined key is pressed (autofire)
*/

template<uint width, uint height>
void CPlayer::ProcessFormFall(int Key_ID, CField<width, height> * const field)
{
    if (m_pForm->Fall(g_pFramework->KeyDown(Key_ID) && !m_bKeyLock_FastDown, field) == false)
    {
        m_bKeyLock_FastDown = true;
    }
    if (!g_pFramework->KeyDown(Key_ID))
    {
        m_bKeyLock_FastDown = false;
    }
}
