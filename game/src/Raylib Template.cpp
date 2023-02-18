#include "raylib.h"
#include "Game.h"

int main()
{
    Game game;

    game.Initialize();
    game.Load();
    game.BeginRun();
    game.GameLoop();
}