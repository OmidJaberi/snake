#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

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
        }

        static auto last_time = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - last_time).count() >= 1)
		{
            std::cout << "\rWaiting...     " << std::endl; // Prevent tabbing
            last_time = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    cleanup();
    return 0;
}
