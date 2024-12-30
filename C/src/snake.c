#include "snake.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool play = false, game = false;

void draw()
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
                printf(MOUSE);
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

void spawn_mouse()
{
    struct point empty_cell[WIDTH * HEIGHT];
    int n = 0;
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (map[i][j] == 0)
            {
                empty_cell[n].x = j;
                empty_cell[n].y = i;
                n++;
            }
    int random = rand() % n;
    struct point* rand_cell = empty_cell + random;
    map[rand_cell->y][rand_cell->x] = -1;
}

void reset(bool start)
{
    game = true;
    play = start;
    dir.x = 1;
    dir.y = 0;
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            map[i][j] = 0;
    map[HEIGHT / 2][WIDTH / 2] = 1;
    snake_size = 2;
    spawn_mouse();
    if (!start)
        message = "Press SPACE to start the game.\nPress Q to quit.";
    draw();
}

void pause_game()
{
    if (play)
    {
        message = "The game is paused. Press SPACE to continue.";
        draw();
    }
    play = !play;
}

void change_dir(int x, int y)
{
    if (!game || !play)
        return;
    if (x * prev_dir.x != 0 || y * prev_dir.y != 0)
        return;
    dir.x = x;
    dir.y = y;
}

void update()
{
    struct point new_head;
    bool new_mouse = false;
    
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (map[i][j] == 1)
            {
                new_head.x = (WIDTH + j + dir.x) % WIDTH;
                new_head.y = (HEIGHT + i + dir.y) % HEIGHT;
            }

    if (map[new_head.y][new_head.x] == -1)
    {
        snake_size++;
        new_mouse = true;
    }
    else if (map[new_head.y][new_head.x] > 0 && map[new_head.y][new_head.x] < snake_size)
    {
        game = false;
        message = "Game over! Press SPACE to play again.";
        return;
    }

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (map[i][j] > 0)
                map[i][j]++;
            if (map[i][j] > snake_size)
                map[i][j] = 0;
        }
    
    map[new_head.y][new_head.x] = 1;
    prev_dir.x = dir.x;
    prev_dir.y = dir.y;
    if (new_mouse) spawn_mouse();
}
