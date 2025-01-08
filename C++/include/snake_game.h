#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <vector>

class SnakeGame
{
private:
    int width, height;
    std::vector <std::pair<int, int> > snake;
    std::pair <int, int> food;
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