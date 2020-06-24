#include "Game.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Game game = Game();
    if(game.Init())
    {
        std::cout << "nice?";
        game.Start();
    }
    else
    {
        std::cout << "wat";
    }
    return 0;
}
