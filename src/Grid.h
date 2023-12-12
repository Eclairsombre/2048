#ifndef GRID
#define GRID

#include <SDL2/SDL.h>
#include "Case.cpp"
#include <iostream>
using namespace std;

class Grid
{
private:
    SDL_Rect rect;
    Case **cases;
    TTF_Font *dogica;
    SDL_Color blanc;

    bool full = false, asMove = false;
    int nbCaseVide = 16;
    int score = 0;

public:
    Grid();
    ~Grid();
    void draw(SDL_Renderer *rend);
    void addRandomCase();
    void handleEvent(SDL_Event &event, bool &stop);
    SDL_Color ColorNumber(int nb);
    void showScore(SDL_Renderer *rend);
};

#endif