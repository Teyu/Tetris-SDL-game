#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "SDL.h"
#include "Singleton.h"

using namespace std;

#define g_pFramework CFramework::Get() //pointer to single entity of CFramework

class CFramework : public TSingleton<CFramework>
{
public:
    bool Init (int screenWidth, int screenHeight, int colorDepth);
    void Quit();
    void Update();
    void Clear();
    void Flip();
    bool KeyDown (int Key_ID);
    SDL_Surface *GetScreen()
    {
        return m_screen;
    }
    int GetScreenWidth()
    {
        return m_screenW;
    }
    int GetScreenHeight()
    {
        return m_screenH;
    }

private:
    SDL_Surface *m_screen;
    Uint8 *m_keystate;
    int m_screenW;
    int m_screenH;
};

#endif //FRAMEWORK_H
