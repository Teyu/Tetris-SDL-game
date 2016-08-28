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
    void calcPointsAndLevel(CPlayer * const player, int numDelLines);
    CForm*  spawnForm(float fSpeedOfFall);

    CForm *m_pForm;
    CPlayer *m_pPlayer;

    bool m_bRunGame;

    float m_fInitSpeed;
};

#endif
