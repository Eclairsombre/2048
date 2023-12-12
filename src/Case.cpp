#include "Case.h"
#include <SDL2/SDL_ttf.h>

Case::Case()
{
    rect.x = 100;
    rect.y = 100;
    rect.w = 200;
    rect.h = 200;
    nb = 0;
    color = {255, 255, 255, 255};
    this->dogica = TTF_OpenFont("font/dogica.ttf", 25);
    if (dogica == NULL)
    {
        fprintf(stderr, "Impossible de charger \"dogica.ttf\"");
        exit(EXIT_FAILURE);
    }
    this->noir = {0, 0, 0};
}

Case::~Case()
{
}

void Case::draw(SDL_Renderer *rend)
{

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &rect);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderDrawRect(rend, &rect);
    this->showNumber(rend);
}

void Case::showNumber(SDL_Renderer *rend)
{
    if (nb != 0)
    {

        std::string number = std::to_string(nb);
        SDL_Surface *textSurface = TTF_RenderText_Blended(dogica, number.c_str(), noir);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
        SDL_FreeSurface(textSurface);

        int textWidth = 0;
        int textHeight = 0;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

        SDL_Rect textRect;
        textRect.x = rect.x + (rect.w - textWidth) / 2;
        textRect.y = rect.y + (rect.h - textHeight) / 2;
        textRect.w = textWidth;
        textRect.h = textHeight;

        SDL_RenderCopy(rend, textTexture, nullptr, &textRect);
        SDL_DestroyTexture(textTexture);
    }
}

void Case::setRect(SDL_Rect rect)
{
    this->rect = rect;
}

void Case::setColor(SDL_Color color)
{
    this->color = color;
}

void Case::setNb(int nb)
{
    this->nb = nb;
}

int Case::getNb()
{
    return nb;
}

void Case::setMove(bool asMove)
{
    this->asMove = asMove;
}

bool Case::getMove()
{
    return asMove;
}