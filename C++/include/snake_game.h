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
    SnakeGame(int _width, int _height) : width(_width), height(_height) { init(); }
    void init();
    bool onSnake(std::pair<int, int>);
    bool onSnake(int x, int y) { return onSnake(std::make_pair(x, y)); }
    bool onFood(std::pair<int, int>);
    bool onFood(int x, int y) { return onFood(std::make_pair(x, y)); }
    bool update();
    bool changeDir(std::pair<int, int> dir);
    bool changeDir(int dx, int dy) { return changeDir(std::make_pair(dx, dy)); }
    bool pause();

    int getWidth();
    int getHeight();
    int getScore();
    bool isRunning();
};

#endif
