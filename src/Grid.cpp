#include "Grid.h"

Grid::Grid()
{
    this->rect.x = 100;
    this->rect.y = 100;
    this->rect.w = 900;
    this->rect.h = 900;

    this->blanc = {255, 255, 255};

    this->dogica = TTF_OpenFont("font/dogica.ttf", 25);
    if (dogica == NULL)
    {
        fprintf(stderr, "Impossible de charger \"dogica.ttf\"");
        exit(EXIT_FAILURE);
    }

    this->cases = new Case *[4];
    for (int i = 0; i < 4; i++)
    {
        this->cases[i] = new Case[4];
    }

    SDL_Rect temp;
    temp.w = 200;
    temp.h = 200;
    temp.x = 100;
    temp.y = 100;

    for (int i = 0; i < 4; i++)
    {
        for (int y = 0; y < 4; y++)
        {
            this->cases[i][y].setRect(temp);
            this->cases[i][y].setNb(0);
            this->cases[i][y].setColor({255, 255, 255, 255});
            temp.x += 200;
        }
        temp.x = 100;
        temp.y += 200;
    }
}

Grid::~Grid()
{
    for (int i = 0; i < 4; i++)
    {
        delete[] this->cases[i];
    }
    delete[] this->cases;
}

void Grid::draw(SDL_Renderer *rend)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, &this->rect);

    for (int i = 0; i < 4; i++)
    {
        for (int y = 0; y < 4; y++)
        {
            this->cases[i][y].draw(rend);
        }
    }
}

void Grid::addRandomCase()
{
    if (this->nbCaseVide > 0)
    {
        int x = rand() % 4;
        int y = rand() % 4;
        while (cases[x][y].getNb() != 0)
        {
            x = rand() % 4;
            y = rand() % 4;
        }
        this->cases[x][y].setNb(2);
        this->cases[x][y].setColor({238, 228, 218, 255});
        this->nbCaseVide--;
    }
    else
    {
        this->full = true;
    }
}

void Grid::handleEvent(SDL_Event &event, bool &stop)
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            stop = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:

                for (int i = 0; i < 4; i++)
                {
                    for (int y = 0; y < 4; y++)
                    {
                        if (cases[i][y].getNb() != 0)
                        {
                            int temp = y;
                            while (temp > 0 && cases[i][temp - 1].getNb() == 0)
                            {
                                this->cases[i][temp - 1].setNb(this->cases[i][temp].getNb());
                                this->cases[i][temp].setNb(0);
                                this->cases[i][temp - 1].setColor(this->ColorNumber(this->cases[i][temp - 1].getNb()));
                                this->cases[i][temp].setColor({255, 255, 255, 255});
                                temp--;
                                this->asMove = true;
                            }
                            if (temp > 0 && this->cases[i][temp - 1].getNb() == this->cases[i][temp].getNb() && this->cases[i][temp - 1].getMove() == false)
                            {

                                this->cases[i][temp - 1].setNb(this->cases[i][temp].getNb() * 2);
                                this->cases[i][temp - 1].setColor(this->ColorNumber(cases[i][temp - 1].getNb()));
                                this->cases[i][temp].setColor({255, 255, 255, 255});
                                this->cases[i][temp].setNb(0);
                                this->nbCaseVide++;
                                this->asMove = true;
                                this->score += this->cases[temp + 1][y].getNb();
                                this->cases[i][temp - 1].setMove(true);
                            }
                        }
                    }
                }
                if (this->asMove)
                {
                    this->addRandomCase();
                    this->asMove = false;
                }
                break;
            case SDLK_RIGHT:
                for (int i = 0; i < 4; i++)
                {
                    for (int y = 3; y >= 0; y--)
                    {
                        if (this->cases[i][y].getNb() != 0)
                        {
                            int temp = y;
                            while (temp < 3 && this->cases[i][temp + 1].getNb() == 0)
                            {
                                this->cases[i][temp + 1].setNb(this->cases[i][temp].getNb());
                                this->cases[i][temp].setNb(0);
                                this->cases[i][temp + 1].setColor(this->ColorNumber(this->cases[i][temp + 1].getNb()));
                                this->cases[i][temp].setColor({255, 255, 255, 255});
                                temp++;
                                this->asMove = true;
                            }
                            if (temp < 3 && this->cases[i][temp + 1].getNb() == this->cases[i][temp].getNb() && this->cases[i][temp + 1].getMove() == false)
                            {
                                this->cases[i][temp + 1].setNb(this->cases[i][temp].getNb() * 2);
                                this->cases[i][temp + 1].setColor(this->ColorNumber(this->cases[i][temp + 1].getNb()));
                                this->cases[i][temp].setColor({255, 255, 255, 255});
                                this->cases[i][temp].setNb(0);
                                this->nbCaseVide++;
                                this->asMove = true;
                                this->score += this->cases[temp + 1][y].getNb();
                                this->cases[i][temp - 1].setMove(true);
                            }
                        }
                    }
                }
                if (this->asMove)
                {
                    this->addRandomCase();
                    this->asMove = false;
                }

                break;
            case SDLK_UP:
                for (int i = 0; i < 4; i++)
                {
                    for (int y = 0; y < 4; y++)
                    {
                        if (this->cases[i][y].getNb() != 0)
                        {
                            int temp = i;
                            while (temp > 0 && this->cases[temp - 1][y].getNb() == 0)
                            {
                                this->cases[temp - 1][y].setNb(this->cases[temp][y].getNb());
                                this->cases[temp][y].setNb(0);
                                this->cases[temp - 1][y].setColor(this->ColorNumber(this->cases[temp - 1][y].getNb()));
                                this->cases[temp][y].setColor({255, 255, 255, 255});
                                temp--;
                                this->asMove = true;
                            }
                            if (temp > 0 && this->cases[temp - 1][y].getNb() == this->cases[temp][y].getNb() && this->cases[temp - 1][y].getMove() == false)
                            {
                                this->cases[temp - 1][y].setNb(this->cases[temp][y].getNb() * 2);
                                this->cases[temp - 1][y].setColor(this->ColorNumber(this->cases[temp - 1][y].getNb()));
                                this->cases[temp][y].setColor({255, 255, 255, 255});
                                this->cases[temp][y].setNb(0);
                                this->nbCaseVide++;
                                this->asMove = true;
                                this->score += this->cases[temp + 1][y].getNb();
                                this->cases[i][temp - 1].setMove(true);
                            }
                        }
                    }
                }
                if (this->asMove)
                {
                    this->addRandomCase();
                    this->asMove = false;
                }

                break;
            case SDLK_DOWN:
                for (int i = 3; i >= 0; i--)
                {
                    for (int y = 0; y < 4; y++)
                    {
                        if (this->cases[i][y].getNb() != 0)
                        {
                            int temp = i;
                            while (temp < 3 && this->cases[temp + 1][y].getNb() == 0)
                            {
                                this->cases[temp + 1][y].setNb(this->cases[temp][y].getNb());
                                this->cases[temp][y].setNb(0);
                                this->cases[temp + 1][y].setColor(this->ColorNumber(this->cases[temp + 1][y].getNb()));
                                this->cases[temp][y].setColor({255, 255, 255, 255});
                                temp++;
                                this->asMove = true;
                            }
                            if (temp < 3 && this->cases[temp + 1][y].getNb() == this->cases[temp][y].getNb() && this->cases[temp + 1][y].getMove() == false)
                            {
                                this->cases[temp + 1][y].setNb(cases[temp][y].getNb() * 2);
                                this->cases[temp + 1][y].setColor(this->ColorNumber(cases[temp + 1][y].getNb()));
                                this->cases[temp][y].setColor({255, 255, 255, 255});
                                this->cases[temp][y].setNb(0);
                                this->nbCaseVide++;
                                this->asMove = true;
                                this->score += cases[temp + 1][y].getNb();
                                this->cases[i][temp - 1].setMove(true);
                            }
                        }
                    }
                }
                if (this->asMove)
                {
                    this->addRandomCase();
                    this->asMove = false;
                }

                break;
            }
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int y = 0; y < 4; y++)
        {
            this->cases[i][y].setMove(false);
        }
    }
}

SDL_Color Grid::ColorNumber(int nb)
{
    SDL_Color color;
    switch (nb)
    {
    case 2:
        color = {238, 228, 218, 255};
        break;
    case 4:
        color = {237, 224, 200, 255};
        break;
    case 8:
        color = {242, 177, 121, 255};
        break;
    case 16:
        color = {245, 149, 99, 255};
        break;
    case 32:
        color = {246, 124, 95, 255};
        break;
    case 64:
        color = {246, 94, 59, 255};
        break;
    case 128:
        color = {242, 223, 168, 255};
        break;
    case 256:
        color = {237, 204, 97, 255};
        break;
    case 512:
        color = {237, 200, 80, 255};
        break;
    case 1024:
        color = {237, 197, 63, 255};
        break;
    case 2048:
        color = {240, 203, 75, 255};
        break;
    case 4096:
        color = {183, 133, 171, 255};
        break;

    default:
        color = {170, 96, 166, 255};
        break;
    }
    return color;
}

void Grid::showScore(SDL_Renderer *rend)
{
    std::string number = std::to_string(score);
    number = "Score : " + number;
    SDL_Surface *textSurface = TTF_RenderText_Blended(dogica, number.c_str(), blanc);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
    SDL_FreeSurface(textSurface);

    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textRect;
    textRect.x = 100;
    textRect.y = 50;
    textRect.w = textWidth;
    textRect.h = textHeight;

    SDL_RenderCopy(rend, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}
