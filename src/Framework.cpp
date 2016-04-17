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
	m_ptext_points = TTF_RenderText_Solid(font, "Punkte: ", text_color);
	m_ptext_level = TTF_RenderText_Solid(font, "Level: ", text_color);

	if (m_ptext_points == NULL)
	{
		cout << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
		
		Quit();
      
		return false;
	}


	m_pKeystate = SDL_GetKeyState(NULL);

	ScreenW = ScreenWidth;
	ScreenH = ScreenHeight;

	return true;
}

/****************************************************************************************************************************************************
shut down framework
*/

void CFramework::Quit()
{
	TTF_Quit();
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
	//display text
	SDL_Rect Pos_points;
	SDL_Rect Pos_level;
	Pos_points.x = 320;
	Pos_level.x = 320;
	Pos_points.y = 10;
	Pos_level.y = 40;
	Pos_points.w = m_ptext_points->w;
	Pos_level.w = m_ptext_level->w;
	Pos_points.h = m_ptext_points->h;
	Pos_level.h = m_ptext_level->h;

	if (SDL_BlitSurface(m_ptext_points, NULL, m_pScreen, &Pos_points) != 0)
      { 
	 cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
      }
	if (SDL_BlitSurface(m_ptext_level, NULL, m_pScreen, &Pos_level) != 0)
      { 
	cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
      }

	SDL_Surface *text;
	stringstream s; 
	s << g_pPlayer->GetPoints();
	text = TTF_RenderText_Solid(font, s.str().c_str(), text_color);
	Pos_points.x += Pos_points.w; 
	Pos_points.w = text->w;
	Pos_points.h = text->h;

	if (SDL_BlitSurface(text, NULL, m_pScreen, &Pos_points) != 0)
      { 
		  cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
      }

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
