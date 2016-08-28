#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "TetrisForms.h"
#include "Framework.h"

class CPlayer
{
public:
    CPlayer() : m_pForm(nullptr), m_Points(0), m_DelLines(0), m_level(1)
    { }

    template<uint width, uint height>
    void Update(CField<width, height> * const field);

    void passForm(CForm * const Form){m_pForm = Form;}
    CForm* GetForm() {return m_pForm;}

    void IncreaseLevel() {m_level++;}
    void IncreasePoints(unsigned Points) { m_Points += Points;}

    unsigned GetPoints() {return m_Points;}
    unsigned GetLevel() {return m_level;}
    unsigned GetDelLines() {return m_DelLines;}

private:
    template<uint width, uint height>
    void ProcessRotateForm(int Key_ID, CField<width, height> * const field);
    template<uint width, uint height>
    void ProcessMoveForm(int Key_ID_Right, int Key_ID_Left, CField<width, height> * const field);
    template<uint width, uint height>
    void ProcessMoveForm(int Key_ID, bool &bKeyLockMove, float &fAutoMoveCount, CField<width, height> * const field);
    template<uint width, uint height>
    void ProcessFormFall(int Key_ID, CField<width, height> * const field); //TODO:make function Form::Update for falling process
    CForm *m_pForm;

    unsigned m_Points;
    unsigned m_DelLines;
    unsigned m_level;

    bool m_bKeyLock_MoveR;
    bool m_bKeyLock_MoveL;
    bool m_bKeyLock_Rotate;
    bool m_bKeyLock_FastDown;

    float m_fAutoMoveCount_l;
    float m_fAutoMoveCount_r;
    const float buffer = 0.2f;
};

#include "../src/Player.inl"

#endif
