#include "SDL.h"
#include "SDL_ttf.h"
#include "Framework.h"
#include "Game.h"

int main( int argc, char* args[] )
{
	//Framework initialisieren: EMPFEHLE WIDTH AUF 500 ZU SETZEN
	if (g_pFramework->Init(500, 600, 16, false) == false)
		return 0;

	CGame Game;

	Game.Init();
	Game.Run();
	Game.Quit();

	//Framework beenden:
	g_pFramework->Quit();
	g_pFramework->Del();

	return 0;
}