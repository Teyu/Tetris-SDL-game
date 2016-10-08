#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "Framework.h"
#include "Controls.h"

class CPlayer
{
public:
    CPlayer() : m_pForm(nullptr), m_pControls(new CControls), m_Points(0), m_DelLines(0), m_level(1)
    { }
    void Init(CControls &controls)
    {
        m_pControls->Init(controls.getKeySettings());
    }

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
    CForm *m_pForm;
    CControls *m_pControls;

    unsigned m_Points;
    unsigned m_DelLines;
    unsigned m_level;
};

#include "../src/Player.inl"

#endif
