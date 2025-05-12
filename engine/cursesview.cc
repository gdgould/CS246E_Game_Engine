#include "cursesview.h"
#include <ncurses.h>
#include <iostream>
namespace age {

CursesView::CursesView(const bool &runningEnhanced): runningEnhanced{runningEnhanced} {
    for (int i = 0; i < GAMEHEIGHT; i++) {
        vector<double> row;
        for (int j = 0; j < GAMEWIDTH; ++j){
            row.emplace_back(0.0);
        }
        heights.emplace_back(row);
    }
    // Initializes curses mode
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    cbreak(); // Don't require newlines
    curs_set(0); // Invisible cursor
    if (has_colors()) { start_color(); }
}
CursesView::~CursesView() {
    // Exits curses mode
    endwin();
}

void CursesView::update(Location location, char character, double height) {
    update(location, character, height, DEFAULTCOLOUR);
}

void CursesView::update(Location location, char character, double height, int cursesColourPair) {
    if (location.x < LEFTBORDER || location.x > RIGHTBORDER || location.y < TOPBORDER || location.y > BOTTOMBORDER) { return; }
    if (heights[location.y][location.x] <= height) {
        heights[location.y][location.x] = height;

        // Colour is an extra feature, so it must be disableable
        if (runningEnhanced && cursesColourPair != DEFAULTCOLOUR) { attron(COLOR_PAIR(cursesColourPair)); }
        mvaddch(location.y, location.x, character);
        if (runningEnhanced && cursesColourPair != DEFAULTCOLOUR) { attroff(COLOR_PAIR(cursesColourPair)); }
    }
}

void CursesView::updateStatusOne(string s) {
    mvaddstr(GAMEHEIGHT, 0, "                                                                                ");
    mvaddstr(GAMEHEIGHT, 0, s.c_str());
}
void CursesView::updateStatusTwo(string s) {
    mvaddstr(GAMEHEIGHT + 1, 0, "                                                                                ");
    mvaddstr(GAMEHEIGHT + 1, 0, s.c_str());
}
void CursesView::updateStatusThree(string s) {
    mvaddstr(GAMEHEIGHT + 2, 0, "                                                                                ");
    mvaddstr(GAMEHEIGHT + 2, 0, s.c_str());
}


void CursesView::resetHeights() {
    for (size_t i = 0; i < heights.size(); i++) {
        for (size_t j = 0; j < heights[i].size(); j++) {
            heights[i][j] = -1000000;
        }
    }
}

void CursesView::displayView() {
    // Updates the terminal with the characters we've added to the buffer
    refresh();
}
void CursesView::clearView() {
    resetHeights();
    for (size_t i = 1; i < GAMEHEIGHT - 1; i++)
    {
        mvaddstr(i, 1, "                                                                              ");
    }
}

}
