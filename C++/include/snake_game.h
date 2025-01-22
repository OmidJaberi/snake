#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <deque>

class SnakeGame
{
private:
    static const int score_unit = 50;
    int width, height;
    std::deque <std::pair<unsigned int, unsigned int> > snake;
    std::pair <unsigned int, unsigned int> food;
    std::pair <int, int> dir, prev_dir;
    bool running, paused;
    void spawnFood();
public:
    SnakeGame(int, int);
    bool onSnake(std::pair<int, int>);
    bool onFood(std::pair<int, int>);
    bool update();
    bool changeDir(std::pair<int, int> dir);
    bool pause();

    int getWidth();
    int getHeight();
    int getScore();
    bool isRunning();
};

#endif
