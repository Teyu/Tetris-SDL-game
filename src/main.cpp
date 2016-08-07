#include "SDL.h"
#include "SDL_ttf.h"
#include "Framework.h"
#include "Game.h"

#ifdef _WIN32
#undef main
#endif

int main()
{
	if (g_pFramework->Init(500, 600, 16, false) == false)
		return 0;

    CGame Game;

    Game.Init(30.0f);
	Game.Run();
	Game.Quit();

	g_pFramework->Quit();
	g_pFramework->Del();

	return 0;
}
