#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <deque>

class SnakeGame
{
private:
    int width, height;
    std::deque <std::pair<unsigned int, unsigned int> > snake;
    std::pair <unsigned int, unsigned int> food;
    std::pair <int, int> dir;
    bool running;
    void spawnFood();
public:
    SnakeGame(int, int);
    bool onSnake(std::pair<int, int>);
    bool onFood(std::pair<int, int>);
    void update();
    void changeDir(std::pair<int, int> dir);

    int getWidth();
    int getHeight();
    int getScore();
    bool isRunning();
};

#endif
