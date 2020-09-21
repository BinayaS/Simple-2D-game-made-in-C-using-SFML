#include "Game.h"


int main()
{
    //Setup
    srand(static_cast<unsigned>(time(0)));
    Game game;

    while (game.GetWindowIsOpen())
    {
        game.Update();
        game.Render();
    }

    return 0;
}