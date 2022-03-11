#include <time.h>
#include "Game.h"
using namespace sf;

int main()
{
    srand(time(0));

    Kmk::Minesweeper::Game game(800, 600, 10, 10, 8);

    game.Init();

    while (game.IsOpen())
    {
        game.Update();
    }
    
    return 0;
}