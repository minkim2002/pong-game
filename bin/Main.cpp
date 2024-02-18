#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"

int main(int argc, char **argv)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize!" << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() < 0)
    {
        std::cout << "SDL_ttf could not initialize!" << TTF_GetError() << std::endl;
        return 1;
    }

    // Create window and renderer
    SDL_Window *window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window could not be created!" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created!" << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the game instance
    // Create the game logic instance
    Game pongGame(1024, 768);

    // Event handling
    SDL_Event e;

    // Game loop
    while (pongGame.isGameRunning)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                pongGame.isGameRunning = false;
            }

            pongGame.handleInput(e);
        }

        // Update game state
        pongGame.update(1.0f / 120.0f); // 120 FPS update rate

        // Render game
        pongGame.render(renderer);

        // Small delay to control frame rate
        SDL_Delay(16);
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}