#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#ifdef _WIN32
#include <conio.h>  // For Windows
#else
#include <termios.h>
#include <unistd.h>

int getch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#define WIDTH 15
#define HEIGHT 10

bool running = true;

int map[HEIGHT][WIDTH];

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\e[1;1H\e[2J");
#endif
}

void draw()
{
    clear();
    printf("╔");
    for (int i = 0; i < 2 * WIDTH; i++)
        printf("═");
    printf("╗\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("║");
        for (int j = 0; j < WIDTH; j++)
            printf("%c ", (map[i][j] > 0 ? 'o' : ' '));
        printf("║\n");
    }
    printf("╚");
    for (int i = 0; i < 2 * WIDTH; i++)
        printf("═");
    printf("╝\n");
}

void* keypress_thread(void* arg)
{
    while (running)
    {
        char ch = getch();
        if (ch == 'q')
            running = false;
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
    map[5][5] = 1;
    while (running)
    {
        draw();
        usleep(1000 * 1000);
    }
    pthread_join(thread_id, NULL);
    printf("Program exited gracefully.\n");
    return 0;
}
