#include "Player.h"

/****************************************************************************************************************************************************
update Player
*/

void CPlayer::Update()
{
    int Lines = g_pField->GetDelLines();

    ProcessRotateForm(SDLK_UP);
    ProcessMoveForm(SDLK_RIGHT, SDLK_LEFT);
    ProcessFormFall(SDLK_DOWN);

    g_pField->Update();
    m_DelLines += g_pField->GetDelLines() - Lines;
}

/****************************************************************************************************************************************************
rotate Form if defined Key is pressed (no autofire)
*/

void CPlayer::ProcessRotateForm(int Key_ID)
{
    if ((g_pFramework->KeyDown(Key_ID)) && (!m_bKeyLock_Rotate) /*&& (m_TetrisForm != Square)*/)
    {
        m_pForm->Rotate();

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

void CPlayer::ProcessMoveForm(int Key_ID_Right, int Key_ID_Left)
{
    ProcessMoveForm(Key_ID_Right, m_bKeyLock_MoveR, m_fAutoMoveCount_r);
    ProcessMoveForm(Key_ID_Left, m_bKeyLock_MoveL, m_fAutoMoveCount_l);
}

void CPlayer::ProcessMoveForm(int Key_ID, bool &bKeyLockMove, float &fAutoMoveCount)
{
    if (g_pFramework->KeyDown(Key_ID))
    {
        if (bKeyLockMove) //autofire
        {
            fAutoMoveCount += g_pTimer->GetElapsed();
            if (fAutoMoveCount > buffer)
                m_pForm->Move(Key_ID, true);
        } else
        {
            m_pForm->Move(Key_ID, false);
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

void CPlayer::ProcessFormFall(int Key_ID)
{
    if (m_pForm->Fall(g_pFramework->KeyDown(Key_ID) && !m_bKeyLock_FastDown) == false)
    {
        m_bKeyLock_FastDown = true;
    }
    if (!g_pFramework->KeyDown(Key_ID))
    {
        m_bKeyLock_FastDown = false;
    }
}
