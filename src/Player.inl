


/****************************************************************************************************************************************************
update Player
*/

template<uint width, uint height>
void CPlayer::Update(CField<width,height> * const field)
{
    int Lines = field->GetDelLines();

    field->Update();
    m_DelLines += field->GetDelLines() - Lines;
}

/****************************************************************************************************************************************************
rotate Form if defined Key is pressed (no autofire)
*/

template<uint width, uint height>
void CPlayer::ProcessRotateForm(int Key_ID, CField<width, height> * const field)
{
    if ((g_pFramework->KeyDown(Key_ID)) && (!m_ProcessKeyState.bKeyLock_Rotate))
    {
        m_pForm->Rotate(field);

        m_ProcessKeyState.bKeyLock_Rotate = true;
    }
    else if (!g_pFramework->KeyDown(Key_ID))
    {
        m_ProcessKeyState.bKeyLock_Rotate = false;
    }
}

/****************************************************************************************************************************************************
move Form to the left or right if defined key is pressed, unlock autofire if key is pressed longer than defined buffer time
*/

template<uint width, uint height>
void CPlayer::ProcessMoveForm(int Key_ID_Right, int Key_ID_Left, CField<width, height> * const field)
{
    ProcessMoveForm(Key_ID_Right, m_ProcessKeyState.bKeyLock_MoveR, m_ProcessKeyState.fAutoMoveCnt_r, field);
    ProcessMoveForm(Key_ID_Left, m_ProcessKeyState.bKeyLock_MoveL, m_ProcessKeyState.fAutoMoveCnt_l, field);
}

template<uint width, uint height>
void CPlayer::ProcessMoveForm(int Key_ID, bool &bKeyLockMove, float &fAutoMoveCnt, CField<width, height> * const field)
{
    if (g_pFramework->KeyDown(Key_ID))
    {
        if (bKeyLockMove) //autofire
        {
            fAutoMoveCnt += g_pTimer->GetElapsed();
            if (fAutoMoveCnt > 0.2f)
                m_pForm->Move(Key_ID, true, field);
        } else
        {
            m_pForm->Move(Key_ID, false, field);
            bKeyLockMove = true;
        }
    } else
    {
        bKeyLockMove = false;
        fAutoMoveCnt = 0.0f;
    }
}

/****************************************************************************************************************************************************
form is constantly falling down, let the form fall down faster if defined key is pressed (autofire)
*/

template<uint width, uint height>
void CPlayer::ProcessFormFall(int Key_ID, CField<width, height> * const field)
{
    if (m_pForm->Fall(g_pFramework->KeyDown(Key_ID) && !m_ProcessKeyState.bKeyLock_FastDown, field) == false)
    {
        m_ProcessKeyState.bKeyLock_FastDown = true;
    }
    if (!g_pFramework->KeyDown(Key_ID))
    {
        m_ProcessKeyState.bKeyLock_FastDown = false;
    }
}
