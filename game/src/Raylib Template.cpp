#pragma warning ( push )
#pragma warning ( disable : 26495 )

//#include "raylib.h"
#include "Game.h"

int main()
{
    Game game;

    game.Initialize();
    game.Load();
    game.BeginRun();
    game.GameLoop();
}

#pragma warning ( pop )