#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include "Block.h"
#include <vector>
class Board
{
public:
    // Board constructor.
    Board(int rows, int columns, float blockWidth, float blockHeight);
    // Function to insert a block into the vector of blocks.
    void addBlock(const Block& block);
    // Draws the board, consisting of the gridlines and blocks in play.
    void draw(sf::RenderWindow& window);

    // Returns blockInPlay and the most-recently inserted Block in vector "blocks".
    Block getBlockInPlay() const;
    Block getLastBlock() const;
    // Returns the amount of rows and columns.
    int getRows() const;
    int getColumns() const;
    // Returns the standard width and height of a Block.
    float getBlockWidth() const;
    float getBlockHeight() const;

    // Calls Block's move function, inherited from sf::RectangleShape.
    void moveBlock();
    // Increments blockInPlay by the height of a Block.
    void shiftUp(float x);
    // Shrinks Block by the size of one standard width of a Block.
    void compressPlayBlock(float n);
    // Aligns blockInPlay with the left or right of the most-recently inserted Block in vector "blocks".
    void leftAlign();
    void rightAlign(float n);

    // Called if player has won or lost.
    void toggleWinText();
    void toggleLossText();

private:
    // Rows and columns to represent the dimensions of the grid.
    int rows, columns;
    // Array of gridlines.
    sf::VertexArray gridLines;
    // Vector of blocks.
    std::vector<Block> blocks;
    // Board is built based off the width and height of the blocks.
    float blockWidth, blockHeight;
    // Block representing the block that the player is playing with.
    Block blockInPlay;
    // Private function called by constructor to initialize the gridlines.
    void initializeGridLines();
    // Text outputs for end-of-game, their initializers, and booleans to signal for their use.
    sf::Text gameOverText, gameWonText;
    sf::Font font;
    void initializeTextOptions();
    bool won, lost;
};

#endif //BOARD_H