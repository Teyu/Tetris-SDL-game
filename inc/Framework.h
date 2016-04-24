#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include <sstream>
#include "Timer.h"
#include "Singleton.h"
#include "Player.h"
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
	int GetScreenWidth() { return ScreenW;}
	int GetScreenHeight() { return ScreenH;}

private:
	SDL_Surface *m_pScreen;
	SDL_Surface *m_ptext_points;
	SDL_Surface *m_ptext_level;
	TTF_Font *font;
	SDL_Color text_color;
	Uint8 *m_pKeystate;
	int ScreenW;
	int ScreenH;
};

#endif
