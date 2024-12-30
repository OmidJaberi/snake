#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define WIDTH 15
#define HEIGHT 10
#define SNAKE "🔵"
#define MOUSE "🍎"

extern bool running, play, game;
char *message;

int map[HEIGHT][WIDTH];
int snake_size;
struct point
{
    int x;
    int y;
} dir, prev_dir;

void draw();

void spawn_mouse();

void reset(bool);

void pause_game();

void change_dir(int, int);

void update();

#endif
