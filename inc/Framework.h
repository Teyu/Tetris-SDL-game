#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include <sstream>
#include "Timer.h"
#include "Singleton.h"

using namespace std;

#define g_pFramework CFramework::Get() //pointer to single entity of CFramework

class CFramework : public TSingleton<CFramework>
{
public:
    bool Init (int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen);
    void Quit();
    void Update();
    void Clear();
    void Flip();
    bool KeyDown (int Key_ID);
    SDL_Surface *GetScreen()
    {
        return m_pScreen;
    }
    int GetScreenWidth()
    {
        return m_ScreenW;
    }
    int GetScreenHeight()
    {
        return m_ScreenH;
    }

private:
    SDL_Surface *m_pScreen;
    Uint8 *m_pKeystate;
    int m_ScreenW;
    int m_ScreenH;
};

#endif
