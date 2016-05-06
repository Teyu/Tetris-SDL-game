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
	bool KeyDown( int Key_ID);
	SDL_Surface *GetScreen() { return m_pScreen;}
    int GetScreenWidth() { return m_ScreenW;}
    int GetScreenHeight() { return m_ScreenH;}

    //TEST (defenitive remove later-> CMenu yet to be implemented)
    void RenderMenu(int Points, int Level, int DelLines){
        SDL_Rect Pos_points;
        SDL_Rect Pos_level;
        SDL_Rect Pos_lines;
        Pos_points.x = 320;
        Pos_level.x = 320;
        Pos_lines.x = 320;
        Pos_points.y = 10;
        Pos_level.y = 40;
        Pos_lines.y = 70;
        Pos_points.w = m_ptext_points->w;
        Pos_level.w = m_ptext_level->w;
        Pos_lines.w = m_ptext_lines->w;
        Pos_points.h = m_ptext_points->h;
        Pos_level.h = m_ptext_level->h;
        Pos_lines.h = m_ptext_lines->h;

        if (SDL_BlitSurface(m_ptext_points, NULL, m_pScreen, &Pos_points) != 0)
          {
         cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
          }
        if (SDL_BlitSurface(m_ptext_level, NULL, m_pScreen, &Pos_level) != 0)
          {
        cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
          }
        if (SDL_BlitSurface(m_ptext_lines, NULL, m_pScreen, &Pos_lines) != 0)
          {
        cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
          }

        SDL_Surface *text;
            stringstream sp;
            sp << Points;
            text = TTF_RenderText_Solid(font, sp.str().c_str(), text_color);
            Pos_points.x += Pos_points.w;
            Pos_points.w = text->w;
            Pos_points.h = text->h;

            if (SDL_BlitSurface(text, NULL, m_pScreen, &Pos_points) != 0)
              {
                  cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
              }

            stringstream sl;
            sl << Level;
            text = TTF_RenderText_Solid(font, sl.str().c_str(), text_color);
            Pos_level.x += Pos_level.w;
            Pos_level.w = text->w;
            Pos_level.h = text->h;

            if (SDL_BlitSurface(text, NULL, m_pScreen, &Pos_level) != 0)
              {
                  cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
              }

            stringstream sd;
            sd << DelLines;
            text = TTF_RenderText_Solid(font, sd.str().c_str(), text_color);
            Pos_lines.x += Pos_lines.w;
            Pos_lines.w = text->w;
            Pos_lines.h = text->h;

            if (SDL_BlitSurface(text, NULL, m_pScreen, &Pos_lines) != 0)
              {
                  cout<< "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
              }
    }
    //ENDOFTEST

private:
	SDL_Surface *m_pScreen;
	SDL_Surface *m_ptext_points;
	SDL_Surface *m_ptext_level;
    SDL_Surface *m_ptext_lines;
	TTF_Font *font;
	SDL_Color text_color;
	Uint8 *m_pKeystate;
    int m_ScreenW;
    int m_ScreenH;
};

#endif
