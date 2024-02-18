#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle
{
public:
    Paddle(float initialX, float initialY, float screenWidth, float screenHeight, bool isPlayer);
    void update(float deltaTime, float ballY);
    void render(SDL_Renderer *renderer);
    void reset();
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

private:
    float initialX;
    float initialY;
    float x, y;
    float velocityY;
    float width, height;
    float screenWidth, screenHeight;
    bool isPlayer; // Flag to indicate if the paddle is controlled by the player

    void handleWallCollision();
    void handleBallCollision(float ballY);
};

#endif // PADDLE_H