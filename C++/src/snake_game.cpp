#include "snake_game.h"

SnakeGame::SnakeGame(int _width, int _height) : width(_width), height(_height)
{
    this->snake.push_back(std::make_pair(height / 2, width / 2));
}

bool SnakeGame::onSnake(std::pair<int, int> cell)
{
    return std::find(this->snake.begin(), this->snake.end(), cell) != this->snake.end();
}

bool SnakeGame::onFood(std::pair<int, int> cell)
{
    return this->food == cell;
}

void SnakeGame::update()
{}

void SnakeGame::changeDir(std::pair<int, int> dir)
{
    this->dir = dir;
}

void SnakeGame::spawnFood()
{}

int SnakeGame::getWidth()
{
    return this->width;
}

int SnakeGame::getHeight()
{
    return this->height;
}

int SnakeGame::getScore()
{
    return this->snake.size() - 2;
}

bool SnakeGame::isRunning()
{
    return this->running;
}
