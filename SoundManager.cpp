#include "SoundManager.h"

SoundManager::SoundManager()
{
    if(!backgroundMusic.openFromFile("16bitloop.wav"))
    {
        std::cout << "Error opening sound background music." << std::endl;
        return;
    }

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(25.f);

    if(!lossBuffer.loadFromFile("whah_whah.wav"))
    {
        std::cout << "Error opening sound background music." << std::endl;
        return;
    }
    gameLossSound.setBuffer(lossBuffer);

    if(!winBuffer.loadFromFile("goodresult.wav"))
    {
        std::cout << "Error opening sound background music." << std::endl;
        return;
    }
    gameWinSound.setBuffer(winBuffer);

    if(!blockBuffer.loadFromFile("woohoo.wav"))
    {
        std::cout << "Error opening sound background music." << std::endl;
        return;
    }
    blockDropSound.setBuffer(blockBuffer);
}

void SoundManager::playBackgroundMusic()
{
    backgroundMusic.play();
}
void SoundManager::playLossSound()
{
    gameLossSound.play();
}
void SoundManager::playWinSound()
{
    gameWinSound.play();
}

void SoundManager::playBlockSound()
{
    blockDropSound.play();
}