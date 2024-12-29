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

bool running = true;

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\e[1;1H\e[2J");
#endif
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
    int i = 0;
    while (running)
    {
        clear();
        printf("%d\n", ++i);
        usleep(1000 * 1000);
    }
    pthread_join(thread_id, NULL);
    printf("Program exited gracefully.\n");
    return 0;
}
