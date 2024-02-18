#ifndef WALL_H
#define WALL_H

#include <SDL.h>

class Wall
{
public:
    Wall(int screenWidth, int screenHeight);
    void render(SDL_Renderer *renderer);

private:
    int screenWidth, screenHeight;
};

#endif // WALL_H