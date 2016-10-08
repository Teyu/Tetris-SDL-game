#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <ctime>
#include <cstdlib>

static const uint g_fieldWidth = 10u;
static const uint g_fieldHeight = 20u;

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
    void spawnForm();

    CForm *m_pForm;
    CPlayer *m_pPlayer;
    CField<g_fieldWidth,g_fieldHeight> *m_pField;

    bool m_bRunGame;
    float m_fSpeed;
};

#endif
