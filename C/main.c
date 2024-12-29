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
int snake_size;
struct point
{
    int x;
    int y;
} dir;

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
            if (map[i][j] > 0)
                printf("o ");
            else if (map[i][j] < 0)
                printf("# ");
            else
                printf("  ");
        printf("║\n");
    }
    printf("╚");
    for (int i = 0; i < 2 * WIDTH; i++)
        printf("═");
    printf("╝\n");
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

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (map[i][j] > 0)
                map[i][j]++;
            if (map[i][j] > snake_size)
                map[i][j] = 0;
        }
    map[new_head.y][new_head.x] = 1;
    if (new_mouse) spawn_mouse();
}

void* keypress_thread(void* arg)
{
    while (running)
    {
        char up = 'w', down = 's', right = 'd', left = 'a';
        char ch = getch();
        if (ch == '\033')
        {
            getch();
            ch = getch();
            up = 'A', down = 'B', right = 'C', left = 'D';
        }
        if (ch == 'q')
            running = false;
        else if (ch == up)
        {
            dir.x = 0;
            dir.y = -1;
        }
        else if (ch == down)
        {
            dir.x = 0;
            dir.y = 1;
        }
        else if (ch == right)
        {
            dir.x = 1;
            dir.y = 0;
        }
        else if (ch == left)
        {
            dir.x = -1;
            dir.y = 0;
        }
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
    dir.x = 1;
    dir.y = 0;
    map[5][5] = 1;
    map[4][5] = 2;
    map[4][4] = 3;
    map[5][4] = 4;
    map[1][1] = -1;
    snake_size = 4;
    while (running)
    {
        update();
        draw();
        usleep(200 * 1000);
    }
    pthread_join(thread_id, NULL);
    printf("Program exited gracefully.\n");
    return 0;
}
