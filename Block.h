#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>

class Block : public sf::RectangleShape
{
public:
    // Constructor for Block takes in its width and height. Game will be using 50.f x 50.f by default.
    Block(float width, float height);
    // Copy constructor. Called by Board to copy the previous Block and store it in a vector of Block objects.
    Block(const Block& otherBlock);
    // Functions to set the position and size of Block.
    void setBlockPosition(float x, float y);
    void setBlockSize(float width, float height);
    // Move function to shift Block from left to right.
    void shiftLR();
    // Function to reverse the direction of Block
    void reverseVelocity();
private:
    // Velocity is 50 by default. Block must move in increments of 50.f so that it fits between the gridlines
    // Difficulty (i.e. the speed at which Block travels, will be controlled by sf::Clock)
    float velocity;
};

#endif //BLOCK_H