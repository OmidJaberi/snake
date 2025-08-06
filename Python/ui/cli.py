import sys
import tty
import termios
import select
import threading

class Cli:
    def __init__(self):
        self.__paused = threading.Event()
        self.__paused.clear()
        self.__running = threading.Event()
        self.__running.set()

    def set_key_listener(self, handler):
        listener_thread = threading.Thread(target=self.key_listener, args=(handler, ), daemon=True)
        listener_thread.start()

    def key_listener(self, handler):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setcbreak(fd)
            while True:
                if select.select([sys.stdin], [], [], 0.1)[0]:
                    ch = sys.stdin.read(1)
                    handler(ch)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

    def draw(self, game):
        print("\033[2J\033[H", end='')
        print("╔", end="")
        for i in range(2 * game.get_width()):
            print("═", end = "")
        print("╗")
        for i in range(game.get_height()):
            print("║", end = "")
            for j in range(game.get_width()):
                if game.on_snake(i, j):
                    print('o', end = ' ')
                elif game.on_mouse(i, j):
                    print('#', end = ' ')
                else:
                    print(' ', end = ' ')
            print("║")
        print("╚", end="")
        for i in range(2 * game.get_width()):
            print("═", end = "")
        print("╝")

    def is_running(self):
        return self.__running.is_set()

    def stop(self):
        self.__running.clear()

    def is_paused(self):
        return self.__paused.is_set()

    def toggle_pause(self):
        if self.__paused.is_set():
            self.__paused.clear()
        else:
            print("[Paused]")
            self.__paused.set()
