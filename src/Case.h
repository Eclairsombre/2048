#ifndef CASE
#define CASE

#include <SDL2/SDL.h>

class Case
{
private:
    SDL_Rect rect;
    int x, y;
    int nb;
    SDL_Color color;
    TTF_Font *dogica;
    SDL_Color noir;
    bool asMove = false;

public:
    Case();
    ~Case();
    void draw(SDL_Renderer *rend);
    void showNumber(SDL_Renderer *rend);

    void setRect(SDL_Rect rect);
    void setColor(SDL_Color color);
    void setNb(int nb);
    int getNb();
    void setMove(bool asMove);
    bool getMove();
};

#endif