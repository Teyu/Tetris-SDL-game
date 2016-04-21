#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Framework.h"
#include "Game.h"

int main( int argc, char* args[] )
{
	if (g_pFramework->Init(500, 600, 16, false) == false)
		return 0;

	CGame Game;

	Game.Init();
	Game.Run();
	Game.Quit();

	g_pFramework->Quit();
	g_pFramework->Del();

	return 0;
}
