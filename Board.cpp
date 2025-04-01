#include "Board.h"

// Default settings of Board.
Board::Board(int rows, int columns, float blockWidth, float blockHeight)
: rows(rows), columns(columns), blockWidth(blockWidth), blockHeight(blockHeight), blockInPlay({150,50}), won(false), lost(false)
{
    initializeTextOptions();
    initializeGridLines();
    blockInPlay.setBlockPosition(blockWidth*3, blockHeight*static_cast<float>(rows - 1));
}

void Board::initializeGridLines()
{
    // Set the type of primitives to draw. These are the lines that make up the grid.
    gridLines.setPrimitiveType(sf::Lines);

    // Initializing vertical grid lines.
    for(int i=0; i<=columns; i++)
    {
        gridLines.append(sf::Vertex(sf::Vector2f(static_cast<float>(i)*blockWidth, 0), sf::Color::Cyan));
        gridLines.append(sf::Vertex(sf::Vector2f(static_cast<float>(i)*blockWidth, static_cast<float>(rows)*blockHeight), sf::Color::Cyan));
    }

    // Initializing horizontal grid lines.
    for(int i=0; i<=rows; i++)
    {
        gridLines.append(sf::Vertex(sf::Vector2f(0,static_cast<float>(i)*blockHeight), sf::Color::Cyan));
        gridLines.append(sf::Vertex(sf::Vector2f(static_cast<float>(columns)*blockWidth, static_cast<float>(i)*blockHeight), sf::Color::Cyan));
    }
}

void Board::initializeTextOptions()
{
    if(!font.loadFromFile("FELIXTI.TTF"))
        return;

    // Red for loss.
    gameOverText.setString("GAME OVER");
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(65.f, 200.f);

    // Green for win!
    gameWonText.setString("YOU WIN");
    gameWonText.setFont(font);
    gameWonText.setCharacterSize(40);
    gameWonText.setFillColor(sf::Color::Green);
    gameWonText.setPosition(65.f, 200.f);
}

// Draws the gridlines, blockInPlay, and the vector of Block objects stored in Board.
void Board::draw(sf::RenderWindow& window)
{
    window.draw(gridLines);
    window.draw(blockInPlay);
    for(const auto& c : blocks)
    {
        window.draw(c);
    }
    if(lost == true)
    {
        window.draw(gameOverText);
    }
    else if(won == true)
    {
        window.draw(gameWonText);
    }
}

void Board::addBlock(const Block& block)
{
    blocks.push_back(block);
}

int Board::getRows() const
{
    return rows;
}

int Board::getColumns() const
{
    return columns;
}

float Board::getBlockWidth() const
{
    return blockWidth;
}

float Board::getBlockHeight() const
{
    return blockHeight;
}

void Board::moveBlock()
{
    if(blockInPlay.getPosition().x <= 0 || blockInPlay.getPosition().x >= 350 - blockInPlay.getSize().x)
    {
        blockInPlay.reverseVelocity();
    }
    blockInPlay.shiftLR();
}

Block Board::getBlockInPlay() const
{
    return blockInPlay;
}

void Board::shiftUp(float x)
{
    if(blocks.empty())
    {
        blockInPlay.setBlockPosition(blockInPlay.getPosition().x, blockHeight*static_cast<float>(static_cast<float>(rows) - x));
    }
    else
    {
        blockInPlay.setBlockPosition(blocks.back().getPosition().x, blockHeight*static_cast<float>(static_cast<float>(rows) - x));
    }
}

Block Board::getLastBlock() const
{
    return blocks.back();
}

void Board::compressPlayBlock(float n)
{
    blockInPlay.setSize({blockInPlay.getSize().x - blockWidth*n, blockInPlay.getSize().y});
}

void Board::leftAlign()
{
    blockInPlay.setPosition({blocks.back().getPosition().x, blockInPlay.getPosition().y});
}

void Board::rightAlign(float n)
{
    blockInPlay.setPosition({blocks.back().getPosition().x + blockWidth*n, blockInPlay.getPosition().y});
}

void Board::toggleWinText()
{
    won = true;
}

void Board::toggleLossText()
{
    lost = true;
}