#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>

class Obstacle
{
public:
    Obstacle(float initialX, float initialY, float width, float height);
    void update(float deltaTime);
    bool checkCollision(float ballX, float ballY, float ballRadius) const;
    void render(SDL_Renderer *renderer) const;

private:
    float x, y;
    float width, height;
};

#endif // OBSTACLE_H
