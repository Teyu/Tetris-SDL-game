#include "Framework.h"

/****************************************************************************************************************************************************
initialise
*/

bool CFramework::Init (int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen)
{
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        cout << "SDL could not be initialised" << endl;
        cout << "Error: " << SDL_GetError() << endl;

        Quit();

        return false;
    }

    if (bFullscreen == true)
    {
        m_pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    }
    else
    {
        m_pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth, SDL_HWSURFACE | SDL_DOUBLEBUF);
    }

    if (m_pScreen == NULL)
    {
        cout << "video mode could not be set" << endl;
        cout << "Error: " << SDL_GetError() << endl;

        Quit();

        return false;
    }

    SDL_WM_SetCaption ("Sylwia", "Sylwia");

    m_pKeystate = SDL_GetKeyState (NULL);

    m_ScreenW = ScreenWidth;
    m_ScreenH = ScreenHeight;

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
    return (m_pKeystate[Key_ID] ? true : false);
}

/****************************************************************************************************************************************************
clear framework
*/

void CFramework::Clear()
{
    SDL_FillRect (m_pScreen, NULL, SDL_MapRGB (m_pScreen->format, 0, 0, 0));
}

/****************************************************************************************************************************************************
display on screen
*/

void CFramework::Flip()
{
    SDL_Flip (m_pScreen);
}
