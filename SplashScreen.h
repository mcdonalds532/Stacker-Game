#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H
#include <SFML/Graphics.hpp>

class SplashScreen
{
public:
    SplashScreen();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getStartButtonBounds() const;
private:
    sf::Font font;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text startText, gameTitle, nameAndCRN, courseNameAndTerm;
    sf::RectangleShape startButton;
};

#endif //SPLASHSCREEN_H