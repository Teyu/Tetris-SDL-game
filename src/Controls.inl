/****************************************************************************************************************************************************
rotate Form if defined Key is pressed (no autofire)
*/

template<uint32_t width, uint32_t height>
void CControls::ProcessRotate (CForm &form, CField<width, height> &field)
{
    if (form.GetType() != Square)
    {
        if ( (g_pFramework->KeyDown (Keys.Rotate)) && (!bKeyLock_Rotate))
        {
            form.Rotate (&field);
            bKeyLock_Rotate = true;
        }
        else if (!g_pFramework->KeyDown (Keys.Rotate))
        {
            bKeyLock_Rotate = false;
        }
    }
}

/****************************************************************************************************************************************************
move Form to the left or right if defined key is pressed, unlock autofire if key is pressed longer than defined buffer time
*/

template<uint32_t width, uint32_t height>
void CControls::ProcessMove (CForm &form, CField<width, height> &field)
{
    ProcessMove (Keys.MoveRight, bKeyLock_MoveR, fAutoMoveCnt_r, form, field);
    ProcessMove (Keys.MoveLeft, bKeyLock_MoveL, fAutoMoveCnt_l, form, field);
}

template<uint32_t width, uint32_t height>
void CControls::ProcessMove (uint32_t KeyID, bool &bKeyLockMove, float &fAutoMoveCnt, CForm &form, CField<width, height> &field)
{
    if (g_pFramework->KeyDown (KeyID))
    {
        if (bKeyLockMove) //autofire
        {
            fAutoMoveCnt += g_pTimer->GetElapsed();
            if (fAutoMoveCnt > 0.2f)
            {
                form.Move (KeyID, true, &field);
            }
        }
        else
        {
            form.Move (KeyID, false, &field);
            bKeyLockMove = true;
        }
    }
    else
    {
        bKeyLockMove = false;
        fAutoMoveCnt = 0.0f;
    }
}

/****************************************************************************************************************************************************
form is constantly falling down, let the form fall down faster if defined key is pressed (autofire)
*/

template<uint32_t width, uint32_t height>
void CControls::ProcessFastDown (CForm &form, CField<width, height> &field)
{
    //TEST
    bool docked;
    if (g_pFramework->KeyDown (Keys.FastDown) && !bKeyLock_FastDown)
    {
        docked = form.FallFast (&field);
    }
    else
    {
        docked = form.Fall (&field);
    }
    //
    if (!docked)
    {
        bKeyLock_FastDown = true;
    }
    if (!g_pFramework->KeyDown (Keys.FastDown))
    {
        bKeyLock_FastDown = false;
    }
}
