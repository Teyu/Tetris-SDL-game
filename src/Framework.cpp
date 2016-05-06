#include "Framework.h"

/****************************************************************************************************************************************************
initialise
*/

bool CFramework::Init(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen)
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
		m_pScreen = SDL_SetVideoMode( ScreenWidth, ScreenHeight, ColorDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	} else
	{
		m_pScreen = SDL_SetVideoMode( ScreenWidth, ScreenHeight, ColorDepth, SDL_HWSURFACE | SDL_DOUBLEBUF);
	}

	if (m_pScreen == NULL)
	{
		cout << "video mode could not be set" << endl;
		cout << "Error: " << SDL_GetError() << endl;

		Quit();

		return false;
	}

	SDL_WM_SetCaption("Tetris", "Tetris");

    //TO BE REMOVED LATER...
    if (TTF_Init() != 0)
	{
		cout << "SDL_tff could not be initialised" << endl;
		cout << "Error: " << TTF_GetError() << endl;
      
		Quit();
      
		return false;
	}

	font = TTF_OpenFont("FreeSans.ttf", 24); 

	if (font == NULL)
	{
      cout << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;

      Quit();
      
	  return false;
   }

    SDL_Color color = {255, 255, 255};
	text_color = color; 
    m_ptext_points = TTF_RenderText_Solid(font, "Points: ", text_color);
	m_ptext_level = TTF_RenderText_Solid(font, "Level: ", text_color);
    m_ptext_lines = TTF_RenderText_Solid(font, "Lines: ", text_color);

	if (m_ptext_points == NULL)
	{
		cout << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
		
		Quit();
      
		return false;
    }

    if (m_ptext_level == NULL)
    {
        cout << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;

        Quit();

        return false;
    }

    if (m_ptext_lines == NULL)
    {
        cout << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;

        Quit();

        return false;
    }
    //...TO BE REMOVED LATER


	m_pKeystate = SDL_GetKeyState(NULL);

    m_ScreenW = ScreenWidth;
    m_ScreenH = ScreenHeight;

	return true;
}

/****************************************************************************************************************************************************
shut down framework
*/

void CFramework::Quit()
{
    TTF_Quit(); //TO BE REMOVED LATER
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

bool CFramework::KeyDown( int Key_ID)
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
	//dividing line
	SDL_Rect LineBlock;
	LineBlock.x = 300;
	LineBlock.y = 0;
	LineBlock.w = 2;
	LineBlock.h = 2;
	for (int i = 0; i < (600/2); i++)
	{
		SDL_FillRect(m_pScreen, &LineBlock, SDL_MapRGB (m_pScreen->format, 255, 255, 255));
		LineBlock.y += 2;
	}

	SDL_Flip(m_pScreen);
}
