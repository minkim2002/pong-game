#include "Obstacle.h"

Obstacle::Obstacle(float initialX, float initialY, float width, float height)
    : x(initialX), y(initialY), width(width), height(height)
{
}

void Obstacle::update(float deltaTime)
{
}

void Obstacle::render(SDL_Renderer *renderer) const
{
    // Render the obstacle on the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect obstacleRect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
    SDL_RenderFillRect(renderer, &obstacleRect);
}

bool Obstacle::checkCollision(float ballX, float ballY, float ballRadius) const
{
    // Check if the ball collides with the obstacle
    return (ballX + ballRadius > x && ballX - ballRadius < x + width &&
            ballY + ballRadius > y && ballY - ballRadius < y + height);
}
