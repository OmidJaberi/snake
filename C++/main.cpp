#include <iostream>
#include <thread>
#include <chrono>
#include "snake_game.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

SnakeGame game(10, 10);

void setup()
{
#ifdef _WIN32
    // No setup required for Windows
#else
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE); // Non-blocking input
    keypad(stdscr, TRUE);
#endif
}

void cleanup()
{
#ifdef _WIN32
    // No cleanup required for Windows
#else
    def_prog_mode(); // Retain the screen without clearing
    //endwin();
#endif
}

char getKeyPress()
{
#ifdef _WIN32
    if (_kbhit())
	{
        return _getch();
    }
    return 0;
#else
    int ch = getch();
    if (ch != ERR)
	{
        return ch;
    }
    return 0;
#endif
}

int main()
{
    setup();

    bool running = true;
    while (running) {
        char key = getKeyPress();
        if (key != 0)
		    {
            std::cout << "\rYou pressed: " << key << std::endl;
            if (key == 'q')
			      {
                running = false;
            }
            if (key == 'w')
                game.changeDir(std::make_pair(-1, 0));
            else if (key == 's')
                game.changeDir(std::make_pair(1, 0));
            else if (key == 'a')
                game.changeDir(std::make_pair(0, -1));
            else if (key == 'd')
                game.changeDir(std::make_pair(0, 1));
        }

        static auto last_time = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count() >= 300)
		    {
            std::cout << "\e[1;1H\e[2J";
            for (int i = 0; i < 10; i++)
            {
                std::cout << "\r";
                for (int j = 0; j < 10; j++)
                    if (game.onSnake(std::make_pair(i, j)))
                        std::cout << "# ";
                    else if (game.onFood(std::make_pair(i, j)))
                        std::cout << "@ ";
                    else
                        std::cout << ". ";
                std::cout << std::endl;
            }
            game.update();
            last_time = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    cleanup();
    return 0;
}
