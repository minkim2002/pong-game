#include "Ball.h"
#include <cmath>
#include <SDL2_gfxPrimitives.h>

Ball::Ball(float initialX, float initialY, float screenWidth, float screenHeight)
    : x(initialX), y(initialY), screenWidth(screenWidth), screenHeight(screenHeight)
{
    // Initialize ball properties
    velocityX = 600.0f; // Initial velocity in the x direction
    velocityY = 600.0f; // Initial velocity in the y direction
    radius = 10;
}

void Ball::update(float deltaTime, const Paddle &playerPaddle, const Paddle &cpuPaddle, const std::vector<Obstacle> &obstacles)
{

    // Update ball position based on velocity and time
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;

    // Handle collisions with walls and paddles
    handleWallCollision(Wall(screenWidth, screenHeight));
    handlePaddleCollision(playerPaddle, cpuPaddle);
    handleObstacleCollision(obstacles);
}

void Ball::render(SDL_Renderer *renderer)
{
    // Render the ball on the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    filledCircleRGBA(renderer, static_cast<int>(x), static_cast<int>(y), radius, 255, 255, 255, 255);
}

void Ball::reset()
{
    // Reset ball position to the center of the screen
    x = screenWidth / 2.0f;
    y = screenHeight / 2.0f;
}

void Ball::handleWallCollision(const Wall &wall)
{
    // Handle collisions with top and bottom walls
    if (y - radius < 0 || y + radius > screenHeight)
    {
        velocityY = -velocityY; // Reverse the velocity in the y direction
    }
}

void Ball::handlePaddleCollision(const Paddle &playerPaddle, const Paddle &cpuPaddle)
{
    // Check if the ball collides with the player's paddle
    if (x - radius < playerPaddle.getX() + playerPaddle.getWidth() &&
        x + radius > playerPaddle.getX() &&
        y + radius > playerPaddle.getY() &&
        y - radius < playerPaddle.getY() + playerPaddle.getHeight())
    {
        velocityX = -velocityX; // Reverse the velocity in the x direction

        float perturbation = 0.05f * std::sqrt(velocityX * velocityX + velocityY * velocityY);
        velocityX += perturbation * (2.0f * static_cast<float>(std::rand()) / RAND_MAX - 1.0f);
        velocityY += perturbation * (2.0f * static_cast<float>(std::rand()) / RAND_MAX - 1.0f);
    }

    // Check if the ball collides with the CPU's paddle
    if (x + radius > cpuPaddle.getX() &&
        x - radius < cpuPaddle.getX() + cpuPaddle.getWidth() &&
        y + radius > cpuPaddle.getY() &&
        y - radius < cpuPaddle.getY() + cpuPaddle.getHeight())
    {
        velocityX = -velocityX; // Reverse the velocity in the x direction

        float perturbation = 0.05f * std::sqrt(velocityX * velocityX + velocityY * velocityY);
        velocityX += perturbation * (2.0f * static_cast<float>(std::rand()) / RAND_MAX - 1.0f);
        velocityY += perturbation * (2.0f * static_cast<float>(std::rand()) / RAND_MAX - 1.0f);
    }
}

void Ball::handleObstacleCollision(const std::vector<Obstacle> &obstacles)
{
    for (const auto &obstacle : obstacles)
    {
        // Check for collision with each obstacle
        if (obstacle.checkCollision(x, y, radius))
        {
            velocityX = -velocityX;
            velocityY = velocityY;
        }
    }
}
