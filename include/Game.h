#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Ball.h"
#include "Paddle.h"
#include <SDL_ttf.h>
#include <vector>
#include "Wall.h"
#include "Obstacle.h"

enum class GameState
{
    START,
    RUNNING,
    END
};

class Game
{
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    bool isGameRunning = true;
    void handleInput(SDL_Event &event);
    void update(float deltaTime);
    void render(SDL_Renderer *renderer);

private:
    int screenWidth, screenHeight;
    Ball ball;
    Paddle playerPaddle;
    Paddle cpuPaddle;
    Wall walls;
    int playerScore;
    int cpuScore;
    std::vector<Obstacle> obstacles;
    void createObstacles();
    GameState gameState;
    void resetGame();
    void restartGame();
    void startGame();
    bool gameStarted = false;
    void renderStartScreen(SDL_Renderer *renderer);
    void renderRunningState(SDL_Renderer *renderer);
    void renderEndScreen(SDL_Renderer *renderer);
    void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y);
};

#endif // GAME_H