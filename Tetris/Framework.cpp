#include "Framework.h"

bool CFramework::Init(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen)
{
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		cout << "SDL konnte nicht initialisiert werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

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

	//Prüfen ob alles geklappt hat
	if (m_pScreen == NULL)
	{
		cout << "Videomodus konnte nicht gesetzt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

		return false;
	}

	//Titel der Application setzen:
	SDL_WM_SetCaption("Tetris", "Tetris");

	//SDL_ttf initialisieren
	//WIE WIRD SDL_TTF EINGEBUNDEN?:
	//Führe die gleichen Schritte durch wie beim Einbinden von SDL.lib
	//Kopiere SDL_ttf.lib und die anderen lib-Programme aus dem Biblitotheksverzeichnis in den Projektordner
	//Gebe bei "Zusätzliche Abhängigkeiten" statt SDL.lib, SDLmain.lib, folgendes ein: SDL_ttf.lib

	if (TTF_Init() != 0)
	{
		cout << "SDL_tff konnte nicht initialisiert werden!" << endl;
		cout << "Fehlermeldung: " << TTF_GetError() << endl;
      
		Quit();
      
		return false;
	}

	//einen Fond laden:
	font = TTF_OpenFont("FreeSans.ttf", 24); //Gibt einen Zeiger auf den geladenen Font zurück: 1.Argument: Dateiname, 2.Argument: Größe
	if (font == NULL)
	{
      cout << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;

      Quit();
      
	  return false;
   }

	//Text auf den Bildschirm schreiben:
	SDL_Color color = {255, 255, 255};
	text_color = color; //In weiss
	m_ptext_points = TTF_RenderText_Solid(font, "Punkte: ", text_color);
	m_ptext_level = TTF_RenderText_Solid(font, "Level: ", text_color);
	//Gibt einen Zeiger auf den gerenderten Text zurück: 1. Argument: Font, 2. Argument: Ausgabetext, 3. Argument: Farbe des Textes

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

void CFramework::Quit()
{
	TTF_Quit();
	SDL_Quit();
}

void CFramework::Update()
{
	g_pTimer->Update();
	SDL_PumpEvents(); //Tastaturstatus ermitteln
}

bool CFramework::KeyDown( int Key_ID)
{
	return (m_pKeystate[Key_ID] ? true : false);
}

void CFramework::Clear()
{
	SDL_FillRect (m_pScreen, NULL, SDL_MapRGB (m_pScreen->format, 0, 0, 0));
}

void CFramework::Flip()
{
	//Gebe den Text auf dem Bildschirm aus:
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
      { //1.Parameter: Zeiger auf den Text, 2.Argument: Ausschnitt von Text, der kopiert werden soll, 
		  //3. Argument: Zieloberfläche, 4.Argument: Position auf der Zieloberfläche
         cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
      }
	if (SDL_BlitSurface(m_ptext_level, NULL, m_pScreen, &Pos_level) != 0)
      { //1.Parameter: Zeiger auf den Text, 2.Argument: Ausschnitt von Text, der kopiert werden soll, 
		  //3. Argument: Zieloberfläche, 4.Argument: Position auf der Zieloberfläche
         cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
      }

	//Text ausgeben:
	SDL_Surface *text;
	stringstream s; //Auf diese Weise können Variablen ausgegeben werden!
	s << g_pPlayer->GetPoints();
	text = TTF_RenderText_Solid(font, s.str().c_str(), text_color);
	Pos_points.x += Pos_points.w; //daneben stehen die Punkte
	//Pos.y += Pos.h + 10; //darunter stehen die Punkte
	Pos_points.w = text->w;
	Pos_points.h = text->h;
	//s << g_pPlayer->GetLevel()

	if (SDL_BlitSurface(text, NULL, m_pScreen, &Pos_points) != 0)
      { 
		  cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
      }

	//Trennlinie:
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