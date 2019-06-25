#include "SDL.h"
#include "Framework.h"
#include "Game.h"

#include <SylwiaConfig.h>
#include <iostream>

#ifdef _WIN32
#undef main
#endif

int main()
{
    std::cout << "Sylwia Version " << SYLWIA_VERSION_MAJOR << "." << SYLWIA_VERSION_MINOR << std::endl;

    if (g_pFramework->Init (500, 600, 16) == false)
    {
        return 1;
    }

    CGame Game;

    Game.Init (30.0f);
    Game.Run();
    Game.Quit();

    g_pFramework->Quit();
    g_pFramework->Del();

    return 0;
}
