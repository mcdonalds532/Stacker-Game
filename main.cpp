#include "Board.h"
#include "Game.h"
#include "SplashScreen.h"
#include "SoundManager.h"

int main()
{
    SplashScreen splashscreen;

    Board board(15,7,50.f,50.f);

    SoundManager soundManager;

    Game game(board, splashscreen, soundManager);

    game.run();

    return 0;
}