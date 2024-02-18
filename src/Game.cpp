#include "Game.h"
#include <SDL_ttf.h>
#include <iostream>

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), ball(screenWidth / 2.0f, screenHeight / 2.0f, screenWidth, screenHeight),
      playerPaddle(30.0f, screenHeight / 2.0f - 50.0f, screenWidth, screenHeight, true),
      cpuPaddle(screenWidth - 50.0f, screenHeight / 2.0f - 50.0f, screenWidth, screenHeight, false),
      walls(screenWidth, screenHeight), playerScore(0), cpuScore(0), isGameRunning(true), gameState(GameState::START)
{
    createObstacles();
}

Game::~Game()
{
}

void Game::startGame()
{
    gameState = GameState::RUNNING;
}

void Game::handleInput(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        isGameRunning = false;
        break;
    case SDL_KEYDOWN:
        if (gameState == GameState::START)
        {
            gameStarted = true; // Start the game when any key is pressed during the start state
        }
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            playerPaddle.update(0.1f, ball.getY()); // Move player paddle up
            break;
        case SDLK_DOWN:
            playerPaddle.update(-0.1f, ball.getY()); // Move player paddle down
            break;
        case SDLK_SPACE:
            if (!isGameRunning)
            {
                resetGame(); // Start a new game when space is pressed after game over
            }
            break;
        case SDLK_r:
            if (gameState == GameState::END)
            {
                restartGame();                // Restart the game when 'R' is pressed
                gameState = GameState::START; // Transition back to the start state
                gameStarted = false;          // Reset the game started flag
            }
            break;
        case SDLK_q:
            if (gameState == GameState::END)
            {
                isGameRunning = false; // Quit the game when 'Q' is pressed
            }
            break;
        }
        break;
    case SDL_WINDOWEVENT:
        // Handle window events
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_MAXIMIZED:
            // Handle window resizing or maximization
            screenWidth = event.window.data1;
            screenHeight = event.window.data2;
            // Adjust your rendering logic here if needed
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            // Handle window minimization
            isGameRunning = false; // Pause the game when minimized
            break;
        case SDL_WINDOWEVENT_RESTORED:
            // Handle window restoration
            isGameRunning = true; // Resume the game when restored
            break;
        }
        break;
    }
}

void Game::update(float deltaTime)
{
    float targetY = 0.0f;
    if (isGameRunning)
    {
        switch (gameState)
        {
        case GameState::START:
            if (gameStarted)
            {
                gameState = GameState::RUNNING;
            }
            break;

        case GameState::RUNNING:
            ball.update(deltaTime, playerPaddle, cpuPaddle, obstacles);
            // Simple AI for the CPU-controlled paddle
            targetY = ball.getY();
            if (targetY < cpuPaddle.getY() + cpuPaddle.getHeight() / 2.0f)
            {
                cpuPaddle.update(-deltaTime, ball.getY()); // Move CPU paddle up
            }
            else
            {
                cpuPaddle.update(deltaTime, ball.getY()); // Move CPU paddle down
            }

            if (ball.getX() < 0)
            {
                cpuScore++;
                resetGame();
            }
            else if (ball.getX() > screenWidth)
            {
                playerScore++;
                resetGame();
            }

            if (playerScore >= 11 || cpuScore >= 11)
            {
                gameState = GameState::END;
            }
            break;

        case GameState::END:

            // Display the winner
            std::string winnerText = (playerScore >= 11) ? "Player Wins!" : "CPU Wins!";
            std::cout << winnerText << std::endl;

            // Provide options to restart or quit the game
            std::cout << "Press R to restart or Q to quit." << std::endl;
        }
    }
}

void Game::render(SDL_Renderer *renderer)
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    switch (gameState)
    {
    case GameState::START:
        // Render start screen
        renderStartScreen(renderer);
        break;

    case GameState::RUNNING:
        // Render game components during the running state
        renderRunningState(renderer);
        break;

    case GameState::END:
        // Render end screen
        renderEndScreen(renderer);
        break;
    }

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}

void Game::renderStartScreen(SDL_Renderer *renderer)
{
    // Render start screen components
    SDL_Color textColor = {255, 255, 255};
    TTF_Font *font = TTF_OpenFont("../resource/Arial.ttf", 20);
    if (font == nullptr)
    {
        std::cerr << "Unable to open font!" << std::endl;
        return;
    }

    std::string startText = "Press any key to start the game!";
    renderText(renderer, font, startText.c_str(), textColor,
               (screenWidth - startText.length() * 20) / 2, (screenHeight - 20) / 2);

    TTF_CloseFont(font);
}

void Game::renderRunningState(SDL_Renderer *renderer)
{
    // Render game components during the running state
    walls.render(renderer);
    playerPaddle.render(renderer);
    cpuPaddle.render(renderer);
    ball.render(renderer);

    for (const auto &obstacle : obstacles)
    {
        obstacle.render(renderer);
    }

    // Render scores
    SDL_Color textColor = {255, 255, 255};
    TTF_Font *font = TTF_OpenFont("../resource/Arial.ttf", 20);
    if (font == nullptr)
    {
        std::cerr << "Unable to open font!" << std::endl;
        return;
    }

    // Render player score
    std::string playerScoreText = "Player: " + std::to_string(playerScore);
    renderText(renderer, font, playerScoreText.c_str(), textColor, 10, 10);

    // Render CPU score
    std::string cpuScoreText = "CPU: " + std::to_string(cpuScore);
    renderText(renderer, font, cpuScoreText.c_str(), textColor, screenWidth - 100, 10);

    TTF_CloseFont(font);
}

void Game::renderEndScreen(SDL_Renderer *renderer)
{
    // Render end screen components
    SDL_Color textColor = {255, 255, 255};
    TTF_Font *font = TTF_OpenFont("../resource/Arial.ttf", 20);
    if (font == nullptr)
    {
        std::cerr << "Unable to open font!" << std::endl;
        return;
    }

    std::string winnerText = (playerScore >= 11) ? "Player Wins!" : "CPU Wins!";
    renderText(renderer, font, winnerText.c_str(), textColor,
               (screenWidth - winnerText.length() * 20) / 2, (screenHeight - 20) / 4);

    std::string instructionText = "Press R to restart or Q to quit.";
    renderText(renderer, font, instructionText.c_str(), textColor,
               (screenWidth - instructionText.length() * 20) / 2, (screenHeight - 20) / 2);

    TTF_CloseFont(font);
}

void Game::renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Game::resetGame()
{
    ball.reset();
    playerPaddle.reset();
    cpuPaddle.reset();
}

void Game::restartGame()
{
    ball.reset();
    playerPaddle.reset();
    cpuPaddle.reset();
    playerScore = 0; // Reset player score
    cpuScore = 0;    // Reset CPU score
    isGameRunning = true;
}

void Game::createObstacles()
{
    obstacles.push_back(Obstacle(200.0f, 200.0f, 50.0f, 50.0f));
    obstacles.push_back(Obstacle(500.0f, 400.0f, 30.0f, 70.0f));
}
