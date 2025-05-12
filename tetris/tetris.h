#ifndef TETRIS_H
#define TETRIS_H
#include "../engine/game.h"
#include "piece.h"
#include "keytype.h"
namespace age {

enum Gamestate {STARTMENU, LEVELSELECT, PLAYING, PAUSED, GAMEOVER, ROCKET};

class Tetris : public Game {
    // High scores:
    vector<vector<int>> highScores; // Each entry has score, lines, level

    // In Play varibles
    int score, lines, level;
    Gamestate gameState;
    PieceType currentPiece = PieceType::None;
    PieceType nextPiece = PieceType::None;
    bool nextPieceVisible = true;
    Piece *nextPieceDisplay;
    const int areDuration = 4; // Time between piece spawns
    int areCounter;

    // Statistics:
    vector<int> pieceCounts;

    // Level Select variables
    int levelHover = 0;
    int blinkCounter = 0;
    const int blinkDuration = 20;

    // Game over/rocket variables
    const int gameOverTime = 120;
    const int rocketTravelTime = 480;
    int gameOverCountdown = 0;

    // Textures for cutscenes:
    Texture startMenu;
    Texture levelSelect;
    Texture launchPad;
    Texture gameOver;
    Texture paused;
    Texture cathedralTexture;
    vector<Texture> rockets;

private:
    void defineColourPairs();
    void spawnPiece(); 
    PieceType getRandomPiece();
    bool KeyUp(Keytype k);

    void initializeCutsceneTextures();
    void initializeLevelSelect();
    void drawHighScores(View &v);
    void beginPlay();
    void initializeStatistics();
    void continuePlay();
    void launchRocket();

public:
    Tetris();
    ~Tetris() {}

    void update() override;
    void draw(View &v) override;
    void onStart() override;
    void onStop() override;

    // Interface with the grid
    void endPlay();
    void linesCleared(int x);

};
}

#endif
