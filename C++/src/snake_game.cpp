#include "snake_game.h"
#include <vector>
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame(int _width, int _height) : width(_width), height(_height)
{
    this->snake.push_back(std::make_pair(height / 2, width / 2));
    this->snake.push_back(std::make_pair(height / 2, width / 2));
    this->dir = std::make_pair(0, 1);
    this->spawnFood();
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
{
    std::pair<unsigned int, unsigned int> new_head;
    new_head.first = (this->height + this->snake.front().first + this->dir.first) % this->height;
    new_head.second = (this->width + this->snake.front().second + this->dir.second) % this->width;
    this->snake.push_front(new_head);
    if (this->onFood(new_head))
        this->spawnFood();
    else
        this->snake.pop_back();
}

void SnakeGame::changeDir(std::pair<int, int> dir)
{
    this->dir = dir;
}

void SnakeGame::spawnFood()
{
    std::srand(time(NULL));
    std::vector<std::pair<int, int> > free;
    for (int i = 0; i < this->height; i++)
        for (int j = 0; j < this->width; j++)
        {
            std::pair<int, int> cell = std::make_pair(i, j);
            if (!this->onSnake(cell))
                free.push_back(cell);
        }
    this->food = free[std::rand() % free.size()];
}

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
