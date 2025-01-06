#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "draw.h"

void draw(int map[HEIGHT][WIDTH])
{
    clear();
    printf("Score: %d\n", (snake_size - 2) * 50);
    set_color();
    printf("╔");
    for (int i = 0; i < 2 * WIDTH; i++)
        printf("═");
    printf("╗\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("║");
        for (int j = 0; j < WIDTH; j++)
            if (map[i][j] > 0)
                printf(SNAKE);
            else if (map[i][j] < 0)
                printf(FOOD);
            else
                printf("  ");
        printf("║\n");
    }
    printf("╚");
    for (int i = 0; i < 2 * WIDTH; i++)
        printf("═");
    printf("╝\n");
    reset_color();
    if (message != NULL && strcmp(message, "") != 0)
    {
        printf("\n%s\n", message);
        message = "";
    }
}

void set_message(char* new_message)
{
    message = new_message;
}