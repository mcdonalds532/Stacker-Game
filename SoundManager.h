// All sounds found on freesound.org. Per their website: Users can can copy, modify,
// distribute and perform the sound, even for commercial purposes, all without the need of asking permission to the author.

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>
#include <iostream>
class SoundManager
{
public:
    // The background music will be looped.
    // All other sounds will occur as instances.
    SoundManager();
    void playBackgroundMusic();
    void playLossSound();
    void playWinSound();
    void playBlockSound();
private:
    sf::Music backgroundMusic;
    sf::Sound gameLossSound;
    sf::Sound gameWinSound;
    sf::Sound blockDropSound;
    sf::SoundBuffer lossBuffer;
    sf::SoundBuffer winBuffer;
    sf::SoundBuffer blockBuffer;
};

#endif //SOUNDMANAGER_H