#pragma warning ( push )
#pragma warning ( disable : 26495 )

#include "Game.h"

int main()
{
    Game *game = new Game();

    game->Initialize();
    game->Load();
    game->BeginRun();
    game->GameLoop();

    delete game;
}

#pragma warning ( pop )