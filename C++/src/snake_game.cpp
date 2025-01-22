#include "snake_game.h"
#include <vector>
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame(int _width, int _height) : width(_width), height(_height)
{
    this->running = true;
    this->paused = false;
    this->snake.push_back(std::make_pair(height / 2, width / 2));
    this->snake.push_back(std::make_pair(height / 2, width / 2));
    this->dir = std::make_pair(0, 1);
    this->prev_dir = this->dir;
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

bool SnakeGame::update()
{
    if (!this->running) return false;
    if (this->paused) return true;
    std::pair<unsigned int, unsigned int> new_head;
    new_head.first = (this->height + this->snake.front().first + this->dir.first) % this->height;
    new_head.second = (this->width + this->snake.front().second + this->dir.second) % this->width;
    this->prev_dir = this->dir;
    if (this->onSnake(new_head))
    {
        this->running = false;
        return false;
    }
    this->snake.push_front(new_head);
    if (this->onFood(new_head))
        this->spawnFood();
    else
        this->snake.pop_back();
    return true;
}

bool SnakeGame::changeDir(std::pair<int, int> dir)
{
    if (!this->running || this->paused) return false;
    if (this->prev_dir.first == dir.first || this->prev_dir.second == dir.second)
        return false;
    this->dir = dir;
    return true;
}

void SnakeGame::spawnFood()
{
    if (!this->running) return;
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

bool SnakeGame::pause()
{
    if (!running) return false;
    return (paused = !paused);
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
    return SnakeGame::score_unit * (this->snake.size() - 2);
}

bool SnakeGame::isRunning()
{
    return this->running;
}
