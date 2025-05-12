#include "grid.h"


namespace age {

Grid::Grid(Tetris &t, Location l, int bw, int bh): Entity(), game{t}, boardWidth{2 * bw}, boardHeight{bh} {
    this->location = l;
    for (int i = 0; i < boardHeight; i++) {
        vector<PieceType> row {boardWidth, PieceType::None};
        theGrid.push_back(row);
    }

    // The texture is the outside of the grid, so that pieces have something to collide with
    string side = "";
    for (int i = 0; i < boardHeight + 1; i++) { side += "[]\n"; }
    string base = "";
    for (int i = 0; i < boardWidth; i++) { base += "="; }
    border = Texture(vector<Texture> {Texture(side, Location{-2,1}), Texture(side, Location{boardWidth,1}), Texture(base, Location{0, boardHeight + 1})});
    this->setTexture(border);
}

bool Grid::lineClearAnimationRunning() { return lineClearCounter > 0; }

void Grid::doUpdate(Action a, Action prev, long numTicks) {
    int cleared = 0;
    if (lineClearCounter > 1) {
        --lineClearCounter;
    }
    else if (lineClearCounter == 1) {
        for (int i = 0; i < boardHeight; i++)
        {
            if (isFullLine(i)) {
                ++cleared;
                clearLine(i--);
            }
        }
        lineClearCounter = 0;
        game.linesCleared(cleared);
    }

    // Update our texture to match theGrid, so that collision detection works:
    Texture t;
    for (int i = 0; i < boardHeight; i++) {
        if (isFullLine(i) && (lineClearCounter / lineClearFlipTime) % 2 == 0) { continue; } // Make full lines blink
        for (int j = 0; j < boardWidth; j++) {
            if (theGrid[i][j] != PieceType::None) {
                t.pixels.push_back(Pixel { j, boardHeight - i, Piece::PieceTypeToString(theGrid[i][j])[0], (int)theGrid[i][j] });
            }
        }
    }
    this->setTexture(Texture( vector<Texture>{border, t} ));
}
void Grid::doDraw(View &v) {

}
void Grid::doOtherColliding(const Entity &other, Location before, Location after) {
    // This will only ever collide with a piece, but we can dynamic cast to make sure
    try {
        const Piece& piece = dynamic_cast<const Piece&>(other);
        // We only care if the piece collided on a "down" move:
        if (before.y == after.y) { return; }
        if (before.y <= 1) { game.endPlay(); return; }// A piece landed too high -- we lost.

        Texture t = piece.getSprite();
        for (size_t i = 0; i < t.pixels.size(); i++)
        {
            // Add each pixel of the piece to the grid (the piece will despawn itself automatically)
            int yPos = before.y + t.pixels[i].location.y - this->location.y;
            int xPos = before.x + t.pixels[i].location.x - this->location.x;
            if (yPos <= boardHeight && yPos > 0&& xPos >= 0 && xPos < boardWidth) {
                theGrid[boardHeight - yPos][xPos] = piece.getType();
            }
        }
        nextPiece();
    }
    catch (...) {
        throw;
        // Oops, not a piece.  Do nothing
    }
}

void Grid::clearLine(int line) {
    theGrid.erase(theGrid.begin() + line);
    theGrid.push_back(vector<PieceType> {boardWidth, PieceType::None});
}
void Grid::nextPiece() {
    for (int i = 0; i < boardHeight; i++)
    {
        if (isFullLine(i)) {
            // Start the line clear animation
            lineClearCounter = lineClearTotalTime;
            return;
        }
    }
    // No lines cleared, spawn next piece
    game.linesCleared(0);
}


bool Grid::isFullLine(int line) {
    for (size_t i = 0; i < theGrid[line].size(); i++)
    {
        if (theGrid[line][i] == PieceType::None) { return false; }
    }
    return true;
}

}
