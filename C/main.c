#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
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
#define DELAY_MS 150
#define SNAKE "🔵"
#define MOUSE "🍎"
#define COLOR_DEFAULT "\033[0m"
#define COLOR_MAP "\033[42m\033[37m"

bool running = true, play = false, game = false;
char *message;

int map[HEIGHT][WIDTH];
int snake_size;
struct point
{
    int x;
    int y;
} dir, prev_dir;

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\e[1;1H\e[2J");
#endif
}

void set_color()
{
#ifdef _WIN32
    return;
#else
    printf(COLOR_MAP);
#endif
}

void reset_color()
{
#ifdef _WIN32
    return;
#else
    printf(COLOR_DEFAULT);
#endif
}

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
        else if (ch == ' ')
        {
            if (game)
            {
                if (play)
                {
                    message = "The game is paused. Press SPACE to continue.";
                    draw();
                }
                play = !play;
            }
            else
            {
                reset(true);
            }
        }
        else if (!game || !play)
            continue;
        if (ch == up && prev_dir.x != 0)
        {
            dir.x = 0;
            dir.y = -1;
        }
        else if (ch == down && prev_dir.x != 0)
        {
            dir.x = 0;
            dir.y = 1;
        }
        else if (ch == right && prev_dir.x == 0)
        {
            dir.x = 1;
            dir.y = 0;
        }
        else if (ch == left && prev_dir.x == 0)
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
    reset(false);
    while (running)
    {
        if (game && play)
        {
            update();
            draw();
        }
        usleep(DELAY_MS * 1000);
    }
    pthread_join(thread_id, NULL);
    return 0;
}
