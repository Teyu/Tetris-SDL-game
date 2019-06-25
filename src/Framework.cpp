#include "Framework.h"
#include "Timer.h"

/****************************************************************************************************************************************************
initialise
*/

bool CFramework::Init (int screenWidth, int screenHeight, int colorDepth)
{
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        cout << "SDL could not be initialized" << endl;
        cout << "Error: " << SDL_GetError() << endl;

        Quit();

        return false;
    }

    m_screen = SDL_SetVideoMode (screenWidth, screenHeight, colorDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

    if (m_screen == NULL)
    {
        cout << "video mode could not be set" << endl;
        cout << "Error: " << SDL_GetError() << endl;

        Quit();

        return false;
    }

    SDL_WM_SetCaption ("Sylwia", "Sylwia");

    m_keystate = SDL_GetKeyState (NULL);

    m_screenW = screenWidth;
    m_screenH = screenHeight;

    return true;
}

/****************************************************************************************************************************************************
shut down framework
*/

void CFramework::Quit()
{
    SDL_Quit();
}

/****************************************************************************************************************************************************
update framework
*/

void CFramework::Update()
{
    g_pTimer->Update();
    SDL_PumpEvents();
}

/****************************************************************************************************************************************************
verify if a certain key is pressed
*/

bool CFramework::KeyDown (int Key_ID)
{
    return (m_keystate[Key_ID] ? true : false);
}

/****************************************************************************************************************************************************
clear framework
*/

void CFramework::Clear()
{
    SDL_FillRect (m_screen, NULL, SDL_MapRGB (m_screen->format, 0, 0, 0));
}

/****************************************************************************************************************************************************
display on screen
*/

void CFramework::Flip()
{
    SDL_Flip (m_screen);
}
