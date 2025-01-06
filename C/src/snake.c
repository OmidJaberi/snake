#include "snake.h"
#include "platform.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool play = false, game = false;

void spawn_food()
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
    spawn_food();
    if (!start)
        set_message("Press SPACE to start the game.\nPress Q to quit.");
    draw(map);
}

void pause_game()
{
    if (play)
    {
        set_message("The game is paused. Press SPACE to continue.");
        draw(map);
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
    bool new_food = false;
    
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
        new_food = true;
    }
    else if (map[new_head.y][new_head.x] > 0 && map[new_head.y][new_head.x] < snake_size)
    {
        game = false;
        set_message("Game over! Press SPACE to play again.");
        draw(map);
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
    if (new_food) spawn_food();
    draw(map);
}
