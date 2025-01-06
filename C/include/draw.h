#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include "platform.h"
#include "snake.h"

#define SNAKE "🔵"
#define FOOD "🍎"

char *message;

void draw(int[HEIGHT][WIDTH]);

void set_message(char*);

#endif
