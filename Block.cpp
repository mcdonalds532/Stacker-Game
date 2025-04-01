#include "Block.h"

Block::Block(float width, float height) : velocity(50.f)
{
    this->setSize({width,height});
    this->setFillColor(sf::Color(0, 0, 255, 120));
}

void Block::setBlockPosition(float x, float y)
{
    this->setPosition(x,y);
}

void Block::setBlockSize(float width, float height)
{
    this->setSize({width,height});
}

void Block::shiftLR()
{
    this->move(velocity, 0);
}

void Block::reverseVelocity()
{
    velocity *=-1;
}

Block::Block(const Block& otherBlock)
{
    velocity = otherBlock.velocity;
    this->setSize(otherBlock.getSize());
    this->setFillColor(otherBlock.getFillColor());
    this->setPosition(otherBlock.getPosition());
}