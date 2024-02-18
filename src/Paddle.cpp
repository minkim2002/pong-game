#include "Paddle.h"

Paddle::Paddle(float initialX, float initialY, float screenWidth, float screenHeight, bool isPlayer)
    : initialX(initialX), initialY(initialY), screenWidth(screenWidth), screenHeight(screenHeight), isPlayer(isPlayer)
{
    // Initialize paddle properties
    velocityY = 300.0f;
    width = 10.0f;
    height = 100.0f;
    // Set initial position
    x = initialX;
    y = initialY;
}

void Paddle::update(float deltaTime, float ballY)
{
    // Update paddle position based on velocity and time
    y += velocityY * deltaTime;

    // Handle collisions with walls and ball
    handleWallCollision();
    handleBallCollision(ballY);
}

void Paddle::render(SDL_Renderer *renderer)
{
    // Render the paddle on the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect paddleRect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
    SDL_RenderFillRect(renderer, &paddleRect);
}

float Paddle::getX() const
{
    return x;
}

float Paddle::getY() const
{
    return y;
}

float Paddle::getWidth() const
{
    return width;
}

float Paddle::getHeight() const
{
    return height;
}

void Paddle::handleWallCollision()
{
    // Ensure the paddle stays within the screen boundaries
    if (y < 0)
    {
        y = 0;
    }
    else if (y + height > screenHeight)
    {
        y = screenHeight - height;
    }
}

void Paddle::handleBallCollision(float ballY)
{
    // Check if the ball collides with the paddle
    if (x + width > screenWidth / 2.0f && isPlayer)
    {
        if (ballY + 10 > y && ballY - 10 < y + height)
        {
            // Compute the relative speed between the ball and the paddle
            float relativeSpeedY = ballY - (y + height / 2.0f);

            // Adjust the ball's direction based on the relative speed and direction of the paddle motion
            velocityY = -relativeSpeedY * 0.15f;
        }
    }
    else if (x < screenWidth / 2.0f && !isPlayer)
    {
        if (ballY + 10 > y && ballY - 10 < y + height)
        {
            // Compute the relative speed between the ball and the paddle
            float relativeSpeedY = ballY - (y + height / 2.0f);

            // Adjust the ball's direction based on the relative speed and direction of the paddle motion
            velocityY = -relativeSpeedY * 0.15f;
        }
    }
}

void Paddle::reset()
{
    // Reset the paddle's position to the initial position
    x = initialX;
    y = initialY;
}