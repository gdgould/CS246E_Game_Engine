#include "tetris.h"
#include "../engine/cursesview.h"
#include "../engine/cursescontrol.h"
#include "pieceDrop.h"
#include "piecelr.h"
#include "rocketmovement.h"
#include "grid.h"
#include <iostream>
#include <thread>
#include <ncurses.h>

#include "art.h"

/* TODO
    * Handle command line input and other startup in main.cc
    * Write your game in game1.h / game1.cc
*/

namespace age {

Tetris::Tetris(): score{0}, lines{0}, level{0}, gameState{Gamestate::STARTMENU} {
    AddView(std::move(make_unique<CursesView>(this->runningEnhanced())));
    AddController(std::move(make_unique<CursesKeyboard>()));
    this->collisionType = Game::CollisionType::Iterative;
    setFramerate(60);
    toggleEnhancements(true);
    this->setInputSmoothing(2);

    defineColourPairs();
    srand(0); // Deterministic RNG

    nextPieceDisplay = nullptr;
    nextPieceVisible = false;

    initializeCutsceneTextures();
}

void Tetris::initializeCutsceneTextures() {
    startMenu = Texture { std::string(tetrisart::menuScreen), Location{1,1}, " " };
    levelSelect = Texture { std::string(tetrisart::levelSelect), Location{1,1}, " " };
    launchPad = Texture { std::string(tetrisart::launchpad), Location{1,1}, " " }; 
    gameOver = Texture { std::string(tetrisart::gameover), Location{32, 8}, "" };
    paused = Texture { std::string(tetrisart::paused), Location{32, 8}, "" };
    cathedralTexture = Texture { std::string(tetrisart::cathedral), Location{-3, -11}, " " };

    rockets.push_back( Texture { std::string(tetrisart::rocket1), Location{0, -4}, " " } );
    rockets.push_back( Texture { std::string(tetrisart::rocket2), Location{-1, -6}, " " } );
    rockets.push_back( Texture { std::string(tetrisart::rocket3), Location{-2, -9}, " " } );
    rockets.push_back( Texture { std::string(tetrisart::rocket4), Location{-4, -10}, " " } );
    rockets.push_back( Texture { std::string(tetrisart::rocket5), Location{-2, -6}, " " } );
}

void Tetris::defineColourPairs() {
    init_pair((int)PieceType::I, COLOR_RED, COLOR_BLACK);
    init_pair((int)PieceType::O, COLOR_YELLOW, COLOR_BLACK);
    init_pair((int)PieceType::J, COLOR_BLUE, COLOR_BLACK);
    init_pair((int)PieceType::L, COLOR_WHITE, COLOR_BLACK);
    init_pair((int)PieceType::T, COLOR_CYAN, COLOR_BLACK);
    init_pair((int)PieceType::S, COLOR_MAGENTA, COLOR_BLACK);
    init_pair((int)PieceType::Z, COLOR_GREEN, COLOR_BLACK);
}

bool Tetris::KeyUp(Keytype k) {
    return !KeyDown(getAction(), k) && KeyDown(getPrevAction(), k);
}


void Tetris::update() {
    rand(); // Ensures randomness even though the game is seeded with srand(0);
    if (KeyUp(Keytype::TOGGLEENHANCEMENTS)) { this->toggleEnhancements(!runningEnhanced()); }

    switch (gameState) {
        case Gamestate::STARTMENU:
            if (KeyUp(Keytype::START)) { initializeLevelSelect(); }
            else if (KeyUp(Keytype::B)) { this->stop(); return; }
            break;
        
        case Gamestate::LEVELSELECT:
            ++blinkCounter;
            if (KeyUp(Keytype::B)) { gameState = Gamestate::STARTMENU; }
            if (KeyUp(Keytype::LEFT) && levelHover != 0) { --levelHover; }
            else if (KeyUp(Keytype::RIGHT) && levelHover != 19) { ++levelHover; }
            else if (KeyUp(Keytype::UP) && levelHover >= 5) { levelHover -= 5; }
            else if (KeyUp(Keytype::DOWN) && levelHover <= 14) { levelHover += 5; }
            else if (KeyUp(Keytype::A) || KeyUp(Keytype::START)) { beginPlay(); }
            break;

        case Gamestate::PLAYING:
            if (KeyUp(Keytype::START)) {
                this->setEntityEnableState(false);
                gameState = Gamestate::PAUSED;
                break;
            }
            if (KeyUp(Keytype::SELECT)) {
                nextPieceVisible = !nextPieceVisible;
                if (nextPieceDisplay) { nextPieceDisplay->visible = nextPieceVisible; }
            }
            continuePlay();
            break;

        case Gamestate::PAUSED:
            if (KeyUp(Keytype::START)) {
                this->setEntityEnableState(true);
                gameState = Gamestate::PLAYING;
            }
            break;

        case Gamestate::GAMEOVER:
            if (gameOverCountdown == 1) {
                if (score >= 30000) { launchRocket(); }
                else { initializeLevelSelect(); }
            }
            else if (gameOverCountdown > 1) { 
                if (gameOverCountdown == 2)  { this->ClearEntities(); }
                --gameOverCountdown; 
            }
            break;
        
        case Gamestate::ROCKET:
            if (gameOverCountdown == 1) { initializeLevelSelect(); }
            else if (gameOverCountdown > 1) { 
                if (gameOverCountdown == 2)  { this->ClearEntities(); }
                --gameOverCountdown; 
            }
            break;

        default:
            break;
    }


}

void Tetris::draw(View &v) {
    switch (gameState) {
        case Gamestate::STARTMENU:
            startMenu.drawAt(v, Location{0,0}, 2.0);
            break;
        
        case Gamestate::LEVELSELECT:
            levelSelect.drawAt(v, Location{0,0}, 2.0);
            drawHighScores(v);
            if ((blinkCounter / blinkDuration) % 2 == 0) {
                Location cursor = Location {(levelHover % 5) * 5 + 29, (levelHover / 5) * 2 + 5};
                v.update(cursor, ' ', 3.0);
                v.update(cursor + Location{1,0}, ' ', 3.0);
            }
            break;

        case Gamestate::GAMEOVER:
            gameOver.drawAt(v, Location{0,0}, 3.0);
            goto playing;

        case Gamestate::PAUSED:
            paused.drawAt(v, Location{0,0}, 3.0);
        playing:
        case Gamestate::PLAYING:
            // Statistics
            for (size_t i = 1; i < 8; i++)
            {
                string temp = std::to_string(pieceCounts[i]);
                while (temp.size() < 3) { temp = "0" + temp; }
                v.update(Location{20, 3 * (int)i - 2 + (i == 1 ? 1 : 0)}, temp, 0);
            }
            // Score / lines
            v.update(Location{62, 4}, "SCORE", 0);
            v.update(Location{62, 7}, "LINES", 0);
            v.update(Location{62, 10}, "LEVEL", 0);
            v.update(Location{62, 14}, "NEXT", 0);

            v.update(Location{62, 5}, std::to_string(score), 0);
            v.update(Location{62, 8}, std::to_string(lines), 0);
            v.update(Location{62, 11}, std::to_string(level), 0);

            break;

        case Gamestate::ROCKET:
            launchPad.drawAt(v, Location{0,0}, 0.5);
            string temp = std::to_string(score);
            while (temp.size() < 7) { temp = " " + temp; }
            v.update(Location{40, 4}, temp, 0);

            break;

    }
}

void Tetris::onStart() {

    // Add startup code here (Optional)
}

void Tetris::onStop() {
    // Add stopping code here (Optional)
}

void Tetris::initializeLevelSelect() {
    gameState = Gamestate::LEVELSELECT;
    blinkCounter = 0;
    gameOverCountdown = 0; 
    score = 0;
    lines = 0;
}

void Tetris::drawHighScores(View &v) {
    Location score = Location { 33, 15 };

    for (size_t i = 0; i < 3 && i < highScores.size(); i++)
    {
        string score = std::to_string(highScores[i][0]);
        string lines = std::to_string(highScores[i][1]);
        string level = std::to_string(highScores[i][2]);
        v.update(Location { 39 - score.length(), 16 + i}, score, 4);
        v.update(Location { 46 - lines.length(), 16 + i}, lines, 4);
        v.update(Location { 51 - level.length(), 16 + i}, level, 4);
    }
}

void Tetris::beginPlay() { 
    initializeStatistics();
    level = levelHover;
    unique_ptr<Grid> grid = make_unique<Grid>(*this, Location{32,0});
    grid->height = 1.0;
    AddEntity(std::move(grid));

    nextPieceVisible = true;

    gameState = Gamestate::PLAYING;
    nextPiece = getRandomPiece();
    spawnPiece();
}
void Tetris::continuePlay() {
    if (areCounter > 1) { --areCounter; }
    else if (areCounter == 1) {
        spawnPiece();
        areCounter = 0;
    }
}
void Tetris::endPlay() {
    gameState = Gamestate::GAMEOVER;
    
    // Add a high score
    size_t i = 0;
    while (highScores.size() > i && highScores[i][0] >= score) { ++i; }
    highScores.insert(highScores.begin() + i, {score, lines, level});

    gameOverCountdown = gameOverTime;
}

void Tetris::initializeStatistics() {
    pieceCounts = vector<int>(8, 0);

    for (size_t i = 1; i < 8; i++)
    {
        unique_ptr<Piece> p = make_unique<Piece>((PieceType)i, 0, Location {10 - (i <= 2 ? 2 : 0), 3 * (int)i - 1});
        p->enabled = false;
        p->rotationEnabled = false;
        p->height = 5;
        this->AddEntity(std::move(p));
    }
    unique_ptr<Piece> p = make_unique<Piece>(PieceType::T, 0, Location {10, 3 * (int)PieceType::T - 1});
    p->enabled = false;
    p->rotationEnabled = false;
    p->height = 5;
    this->AddEntity(std::move(p));

}



void Tetris::launchRocket() {
    gameState = Gamestate::ROCKET;
    gameOverCountdown = rocketTravelTime;

    // Rocket
    unique_ptr<Entity> rocket = make_unique<Entity>();
    rocket->location = Location{18,20};
    rocket->height = 0.8;
    // Rocket
    unique_ptr<Entity> cathedral = make_unique<Entity>();
    cathedral->location = Location{50,20};
    cathedral->height = 0.3;
    cathedral->setTexture(cathedralTexture);


    if (score < 50000) { rocket->setTexture(rockets[0]); }
    else if (score < 70000) { rocket->setTexture(rockets[1]); }
    else if (score < 100000) { rocket->setTexture(rockets[2]); }
    else if (score < 120000) { rocket->setTexture(rockets[3]); }
    
    if (score >= 120000) {
        rocket->setTexture(rockets[4]);
        cathedral->addMovementAction(std::move(make_unique<RocketMovement>(getElapsedTicks())));
    }
    else { rocket->addMovementAction(std::move(make_unique<RocketMovement>(getElapsedTicks()))); }

    AddEntity(std::move(rocket));
    AddEntity(std::move(cathedral));
}


// Functions controlling play:

PieceType Tetris::getRandomPiece() {
    // Implement original randomizer???
    int random = rand() % 7 + 1;
    if (random == (int)currentPiece) { random = rand() % 7 + 1; }
    return (PieceType)random;
}

void Tetris::spawnPiece() {
    ++pieceCounts[nextPiece];
    currentPiece = nextPiece;
    nextPiece = getRandomPiece();
    
    // Create the next piece for display
    if (nextPieceDisplay) { nextPieceDisplay->shouldDespawn = true; }
    unique_ptr<Piece> display = make_unique<Piece>(nextPiece, 0, Location{62, 17});
    display->visible = nextPieceVisible;
    display->rotationEnabled = false;
    display->enabled = false;
    nextPieceDisplay = display.get();
    AddEntity(std::move(display));


    vector<int> gravities {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3};
    int grav = level < 29 ? 2 : 1;
    if (level < 19) { grav = gravities[level]; }

    unique_ptr<Piece> piece = make_unique<Piece>(currentPiece, 0, Location{38,-5});
    piece->addMovementAction(std::move(make_unique<PieceDrop>(grav)));
    piece->addMovementAction(std::move(make_unique<PieceLR>(6, 6)));
    piece->height = 1.0;
    AddEntity(std::move(piece));

}

void Tetris::linesCleared(int x) {
    vector<int> lineWorth {0, 40, 100, 300, 1200};
    score += (level + 1) * lineWorth[x];
    lines += x;
    if ((level + 1) * 10 <= lines) {
        ++level;
    }

    // Prepare to spawn the next piece
    areCounter = areDuration;
}

}


