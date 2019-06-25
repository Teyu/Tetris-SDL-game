#include "Game.h"
#include "Framework.h"
#include "Sprite.h"

#include "SylwiaConfig.h"
#include <sstream>

std::string getDataPath(const char * fileName)
{
	std::string fullPath = SYLWIA_DATA_PATH;
	fullPath += "/";
	fullPath += fileName;

	return fullPath;
}

/****************************************************************************************************************************************************
constructor
*/

CGame::CGame()
{}

/****************************************************************************************************************************************************
initialise
*/

void CGame::Init (float fInitSpeed)
{
    //seed random generator
    time_t t;
    srand (time (&t));

    m_fSpeed = fInitSpeed;

    m_bRunGame = true;
}

/****************************************************************************************************************************************************
control, update and render entities
*/

void CGame::Run()
{
    while (m_bRunGame == true)
    {
        ProcessEvents();

        g_pFramework->Update();
        g_pFramework->Clear();

		CSprite ball;
		ball.Load (getDataPath("BlueBlock.bmp"));
		ball.SetPos (15, 15);
		ball.Render();

        g_pFramework->Flip();
    }
}

/****************************************************************************************************************************************************
quit the game
*/

void CGame::Quit()
{
}

/****************************************************************************************************************************************************
verify if a button is pressed to quit the game
*/

void CGame::ProcessEvents()
{
    SDL_Event Event;
    if (SDL_PollEvent (&Event))
    {
        switch (Event.type)
        {
            case (SDL_QUIT) :
                {
                    m_bRunGame = false;
                }
                break;
            case (SDL_KEYDOWN) :
                {
                    if (Event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        m_bRunGame = false;
                    }
                }
                break;
        }
    }
}
