import sys
import tty
import termios
import threading
import time
import select

import models.snake
import ui.cli

paused = threading.Event()
paused.clear()
running = True

game = models.snake.SnakeGame()

def key_listener():
    global running
    global game
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setcbreak(fd)
        while running:
            if select.select([sys.stdin], [], [], 0.1)[0]:
                ch = sys.stdin.read(1)
                if ch == ' ':
                    if paused.is_set():
                        print("[Resumed]")
                        paused.clear()
                    else:
                        print("[Paused]")
                        paused.set()
                elif ch == '\x1b' or ch == 'q':
                    running = False
                elif ch == 'w':
                    game.change_dir(-1, 0)
                elif ch == 's':
                    game.change_dir(1, 0)
                elif ch == 'd':
                    game.change_dir(0, 1)
                elif ch == 'a':
                    game.change_dir(0, -1)

    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

def main():
    global running
    global game
    while running:
        if not paused.is_set():
            ui.cli.draw(game)
            game.update()
        time.sleep(0.2)

if __name__ == "__main__":
    listener_thread = threading.Thread(target=key_listener, daemon=True)
    listener_thread.start()

    main()

