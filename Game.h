#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "SplashScreen.h"
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class Game
{
public:
    Game(Board& board, SplashScreen& splashScreen, SoundManager& soundManager);
    void intro();
    // Detects user input, namely when the start button is pressed.
    void splashScreenEventHandler(sf::RenderWindow& window, sf::Event event);

    void run();
    // Detects user input, namely space bar.
    void eventHandler(sf::RenderWindow& window, sf::Event event);
    // Updates Board and other variables such as level, and lives (blocks) the user has remaining.
    void update();
    // Increments the level every time the player passes a stage
    void levelUp();

    // Checks if the drop was a valid drop. This function calls the functions below.
    bool validateDrop();
    // Drop validators for all three stages of the game.
    bool stageOneValidate();
    bool stageTwoValidate();
    bool stageThreeValidate();

    // Function to check if the game is over. If it is over, the game will terminate.
    void checkGameOver();
    void gameOver();

private:
    Board& board;
    SplashScreen& splashScreen;
    SoundManager& soundManager;
    // Window to draw the objects
    sf::RenderWindow window;
    // Clocks to handle delay and the movement speed of Block.
    sf::Clock clock;
    sf::Clock delayClock;

    // Stage of the game.
    int level;
    // Lives or Blocks remaining. Used to determine the outcome of the game.
    int lives;
    // Used by clock to handle the movement speed of blockInPlay.
    float moveSpeed;
    // Flag to check the pause state of the game.
    bool gamePaused;
};

#endif //GAME_H