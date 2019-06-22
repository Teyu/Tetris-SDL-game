#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <cstdlib>

class CGame
{
public:
    CGame();

    void Init (float fInitSpeed);
    void Run();
    void Quit();

private:
    void ProcessEvents();

    bool m_bRunGame;
    float m_fSpeed;
};

#endif
