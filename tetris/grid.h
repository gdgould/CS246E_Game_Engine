#ifndef GRID_H
#define GRID_H
#include "../engine/entity.h"
#include "piece.h"
#include "tetris.h"
namespace age {

class Grid : public Entity {
private:
    const int lineClearFlipTime = 12;
    const int lineClearTotalTime = 60;
    Tetris &game;
// Outside vector is a vector of rows, each inside is a row
    vector<vector<PieceType>> theGrid;
    int boardWidth, boardHeight;
    int lineClearCounter = 0;
    Texture border;


public:
    Grid(Tetris &t, Location l, int boardWidth = 10, int boardHeight = GAMEHEIGHT - 3);
    ~Grid() {}

    bool lineClearAnimationRunning();
    int getLinesClearedThisFrame();

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;

    void clearLine(int line);
    void nextPiece();
    bool isFullLine(int line);
};

}

#endif
