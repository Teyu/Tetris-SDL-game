/****************************************************************************************************************************************************
update Player
*/

template<uint32_t width, uint32_t height>
void CPlayer::Update (CField<width, height> *const field)
{
    //Zusammenfassen: !?
    m_pControls->ProcessRotate (*m_pForm, *field);
    m_pControls->ProcessMove (*m_pForm, *field);
    m_pControls->ProcessFastDown (*m_pForm, *field);

    int Lines = field->GetDelLines();

    field->Update();
    m_DelLines += field->GetDelLines() - Lines;
}
