#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include "platform.h"
#include "snake.h"

#define DELAY_MS 150

bool running = true;

void* keypress_thread(void* arg)
{
    while (running)
    {
        char up = 'w', down = 's', right = 'd', left = 'a';
        char ch = getch();
        if (ch == '\033') // Arrow Key Press
        {
            getch();
            ch = getch();
            up = 'A', down = 'B', right = 'C', left = 'D';
        }
        if (ch == 'q')
            running = false;
        else if (ch == ' ')
        {
            if (game)
                pause_game();
            else
                reset(true);
        }
        if (ch == up)
            change_dir(0, -1);
        else if (ch == down)
            change_dir(0, 1);
        else if (ch == right)
            change_dir(1, 0);
        else if (ch == left)
            change_dir(-1, 0);
    }
    return NULL;
}

int main()
{
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, keypress_thread, NULL) != 0)
    {
        fprintf(stderr, "Error creating keypress thread\n");
        return 1;
    }
    reset(false);
    while (running)
    {
        if (game && play)
        {
            update();
            //draw();
        }
        usleep(DELAY_MS * 1000);
    }
    pthread_join(thread_id, NULL);
    return 0;
}
