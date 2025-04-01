#include "Game.h"

// Potential changes - Can change the dimensions of the user interface with a parametrized constructor instead.
// For now, the game will be defaulted to this resolution.
Game::Game(Board& board, SplashScreen& splashScreen, SoundManager& soundManager)
: board(board), splashScreen(splashScreen), soundManager(soundManager), level(1),
window(sf::VideoMode({350, 750, 48}), "Stacker"), moveSpeed(100.f), lives(3), gamePaused(true)
{
    window.setFramerateLimit(60);
}

void Game::intro()
{
    while(gamePaused)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            splashScreenEventHandler(window, event);
        }
        window.clear();
        splashScreen.draw(window);
        window.display();
    }
}

void Game::splashScreenEventHandler(sf::RenderWindow& window, sf::Event event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(splashScreen.getStartButtonBounds().contains(sf::Vector2f{sf::Mouse::getPosition(window)}))
        {
            gamePaused = false;
            return;
        }
    }
}

// Main function of the game
void Game::run()
{
    soundManager.playBackgroundMusic();
    intro();
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            eventHandler(window, event);
        }
        // Game will pause for a second when the player drops their Block
        if(gamePaused)
        {
            if(delayClock.getElapsedTime().asSeconds() >= 1)
            {
                gamePaused = false;
            }
        }
        // Game will resume when pause state is false
        if(clock.getElapsedTime().asMilliseconds() >= static_cast<int>(moveSpeed) && gamePaused == false)
        {
            board.moveBlock();
            clock.restart();
        }
        window.clear();
        board.draw(window);
        window.display();
    }
}

void Game::eventHandler(sf::RenderWindow& window, sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space && gamePaused == false)
        {
            soundManager.playBlockSound();
            // Pauses the game when space bar is pressed by the user.
            delayClock.restart();
            while(delayClock.getElapsedTime() <= sf::seconds(1.f))
            {
                gamePaused = true;
            }
            // Then proceeds to the next stage, allowing a second for the user to prepare.
            update();
            delayClock.restart();
        }
    }
}

void Game::update()
{
    if(validateDrop())
    {
        // Calls the copy constructor of Block, then pushes the created Block into Board's vector of Block objects.
        board.addBlock(Block(board.getBlockInPlay()));
        levelUp();
    }
    else
    {
        board.toggleLossText();
        soundManager.playLossSound();
        gameOver();
    }

    // At levels 6 and 10, the difficulty is adjusted, in accordance with the rules of the game.
    if(level == 6 && lives > 2)
    {
        board.compressPlayBlock(1.f);
        lives--;
    }
    else if(level == 10 && lives > 1)
    {
        board.compressPlayBlock(1.f);
        lives--;
    }
    if(level == 16)
    {
        board.toggleWinText();
        soundManager.playWinSound();
        gameOver();
    }
}
// Per level increase, the game movement speed of the block increases to raise the difficulty as the player progresses.
// This is done by decrementing the time intervals at which the block moves, which is controlled by sf::Clock.
void Game::levelUp()
{
    level++;
    moveSpeed -= 4.f;
    board.shiftUp(static_cast<float>(level));
}

// Validators for all three stages of the game.
bool Game::validateDrop()
{
    if(level == 1)
    {
        return true;
    }
    if(level >= 2 && level < 6)
    {
        if(stageOneValidate())
            return true;
    }
    else if(level >= 6 && level < 10)
    {
        if(stageTwoValidate())
            return true;
    }
    else if(level >= 10 && level <= 15)
    {
        if(stageThreeValidate())
            return true;
    }

    return false;
}

// For the validators, if the user has dropped the Block such that it is only partially above the previously dropped Block,
// the game must detect which side it has dropped to and align accordingly (left or right).
// In this case, lives will also be decremented accordingly.
// If the Block is dropped perfectly above the previous Block, no lives are lost.
bool Game::stageOneValidate()
{
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x)
    {
        return true;
    }
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x - board.getBlockWidth()*2.f)
    {
        lives -= 2;
        checkGameOver();
        board.compressPlayBlock(2.f);
        board.leftAlign();
        return true;
    }
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x + board.getBlockWidth()*2.f)
    {
        lives -= 2;
        checkGameOver();
        board.compressPlayBlock(2.f);
        board.rightAlign(2.f);
        return true;
    }
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x - board.getBlockWidth())
    {
        lives -= 1;
        checkGameOver();
        board.compressPlayBlock(1.f);
        board.leftAlign();
        return true;
    }
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x + board.getBlockWidth())
    {
        lives -= 1;
        checkGameOver();
        board.compressPlayBlock(1.f);
        board.rightAlign(1.f);
        return true;
    }

    return false;
}

bool Game::stageTwoValidate()
{
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x)
    {
        return true;
    }
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x - board.getBlockWidth())
    {
        lives -= 1;
        checkGameOver();
        board.compressPlayBlock(1.f);
        board.leftAlign();
        return true;
    }
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x + board.getBlockWidth())
    {
        lives -= 1;
        checkGameOver();
        board.compressPlayBlock(1.f);
        board.rightAlign(1.f);
        return true;
    }

    return false;
}

bool Game::stageThreeValidate()
{
    if(board.getBlockInPlay().getPosition().x == board.getLastBlock().getPosition().x)
        return true;

    return false;
}

// Function to verify whether the user has lost or not. If they have no lives left, gameOver() is called.
void Game::checkGameOver()
{
    if(lives <= 0)
    {
        board.toggleLossText();
        soundManager.playLossSound();
        gameOver();
    }
}

// Displays win or loss text on screen and ends game.
void Game::gameOver()
{
    delayClock.restart();
    while(delayClock.getElapsedTime().asSeconds() < 3)
    {
        window.clear();
        board.draw(window);
        window.display();
    }
    exit(1);
}