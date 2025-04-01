#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
    if(!font.loadFromFile("COPRGTB.TTF"))
        return;

    // Hard-coded the rest of this part. Very frustrating to align/center.
    startButton.setSize({150.f, 80.f});
    startButton.setFillColor(sf::Color::Black);
    startButton.setPosition(100.f, 600.f);
    startButton.setOutlineColor({0, 255, 255});
    startButton.setOutlineThickness(5.f);

    startText.setString("START");
    startText.setCharacterSize(36);
    startText.setFont(font);
    startText.setFillColor({0, 255, 255});

    sf::FloatRect buttonBounds = startButton.getLocalBounds();
    sf::FloatRect textBounds = startText.getLocalBounds();
    startText.setOrigin(textBounds.width/2, textBounds.height/2);
    startText.setPosition(startButton.getPosition().x + buttonBounds.width / static_cast<float>(2.15),
        startButton.getPosition().y + buttonBounds.height / static_cast<float>(3));

    gameTitle.setString("STACKER");
    gameTitle.setFont(font);
    gameTitle.setCharacterSize(50);
    gameTitle.setFillColor(sf::Color({0, 204, 255}));
    gameTitle.setPosition(40.f, 25.f);

    nameAndCRN.setString("programmed by Stephen Li for CS003A:");
    nameAndCRN.setFont(font);
    nameAndCRN.setCharacterSize(14);
    nameAndCRN.setFillColor(sf::Color::Magenta);
    nameAndCRN.setPosition(20.f, 715.f);

    courseNameAndTerm.setString("Intro to Object-Oriented Programming (C++), Fall 2024");
    courseNameAndTerm.setFont(font);
    courseNameAndTerm.setCharacterSize(10);
    courseNameAndTerm.setFillColor(sf::Color::Magenta);
    courseNameAndTerm.setPosition(10.f, 730.f);

    texture.loadFromFile("stackerDisplay.jpg");
    sprite.setTexture(texture);
    sprite.setScale(0.25f, 0.25f);
    sprite.setPosition(30.f, 115.f);
}

void SplashScreen::draw(sf::RenderWindow& window)
{
    window.draw(startButton);
    window.draw(startText);
    window.draw(gameTitle);
    window.draw(nameAndCRN);
    window.draw(courseNameAndTerm);
    window.draw(sprite);
}

sf::FloatRect SplashScreen::getStartButtonBounds() const
{
    return startButton.getGlobalBounds();
}