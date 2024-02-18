#include "Wall.h"
#include <SDL2_gfxPrimitives.h>

Wall::Wall(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight)
{
}

void Wall::render(SDL_Renderer *renderer)
{
    // Render the top and bottom walls on the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    thickLineRGBA(renderer, 0, 0, screenWidth, 0, 8, 255, 255, 255, 255);
    thickLineRGBA(renderer, 0, screenHeight, screenWidth, screenHeight, 8, 255, 255, 255, 255);
}