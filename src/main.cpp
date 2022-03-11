#include <time.h>
#include "Game.h"
using namespace sf;

// TODO: Принимать из терминала параметры для игры
int main()
{
    srand(time(0));

    Kmk::Minesweeper::Game game(800, 600, 10, 5, 3);

    game.Init();

    while (game.IsPlaying())
    {
        game.Update();
    }

    return 0;
}