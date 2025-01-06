#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

extern bool play, game;

int map[HEIGHT][WIDTH];
int snake_size;
struct point
{
    int x;
    int y;
} dir, prev_dir;

void spawn_food();

void reset(bool);

void pause_game();

void change_dir(int, int);

void update();

#endif
