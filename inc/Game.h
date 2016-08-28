#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <ctime>
#include <cstdlib>

class CGame
{
public:
    CGame();

    void Init(float fInitSpeed);
    void Run();
    void Quit();

private:
    void ProcessEvents();
    CForm*  spawnForm(float fSpeedOfFall);

    enum Form{Bar, Square, L, J, Z, S, T};
    Form m_TetrisForm;

    CForm *m_pForm;
    CPlayer *m_pPlayer;
    CField<10u,20u> *m_pField;

    bool m_bGameRun;

    float m_fInitSpeed;
};

#endif
