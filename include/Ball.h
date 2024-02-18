#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "Paddle.h"
#include "Wall.h"
#include <vector>
#include "Obstacle.h"

class Ball
{
public:
    Ball(float initialX, float initialY, float screenWidth, float screenHeight);
    void update(float deltaTime, const Paddle &playerPaddle, const Paddle &cpuPaddle, const std::vector<Obstacle> &obstacles);
    void render(SDL_Renderer *renderer);
    float getX() const { return x; }
    float getY() const { return y; }
    void reset();

private:
    float x, y;
    float velocityX, velocityY;
    int radius;
    float screenWidth, screenHeight;
    void handleWallCollision(const Wall &wall);
    void handlePaddleCollision(const Paddle &playerPaddle, const Paddle &cpuPaddle);
    void handleObstacleCollision(const std::vector<Obstacle> &obstacles);
};

#endif // BALL_H