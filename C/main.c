#include <stdio.h>

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

int main()
{
    char c = getch();
    printf("Char: %c\n", c);
    return 0;
}
