import os
import sys
import tty
import termios
import select
import threading
import time

class Cli:
    snake = "🔵"
    mouse = "🍎"
    grass = "  "
    def __init__(self, game):
        self.__paused = threading.Event()
        self.__paused.set()
        self.__running = threading.Event()
        self.__running.set()
        self.__game = game
        self.draw()

    def set_key_listener(self, handler):
        listener_thread = threading.Thread(target=self.key_listener, args=(handler, ), daemon=True)
        listener_thread.start()

    def key_listener(self, handler):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setcbreak(fd)
            while True:
                r, _, _ = select.select([fd], [], [], 0.1)
                if not r:
                    continue
                b = os.read(fd, 1)
                if not b:
                    continue
                if b == b'\x1b':
                    time.sleep(0.02)
                    extra = b''
                    while select.select([fd], [], [], 0)[0]:
                        extra += os.read(fd, 32)
                    b = b + extra
                ch = b.decode('utf-8', errors='ignore')
                handler(ch)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

    def show_message(self, message):
        if message:
            print(f"\n{message}")

    def draw(self):
        os.system('cls' if os.name == 'nt' else 'clear')
        print(f"Score: {self.__game.get_score()}")
        self.begin_grass()
        print("╔" + "═" * (2 * self.__game.get_width()) + "╗")
        for i in range(self.__game.get_height()):
            row = "".join(
                (Cli.snake if self.__game.on_snake(i, j) else
                 Cli.mouse if self.__game.on_mouse(i, j) else Cli.grass)
                for j in range(self.__game.get_width())
            )
            print(f"║{row}║")
        print("╚" + "═" * (2 * self.__game.get_width()) + "╝", end="")
        self.end_grass()

    def begin_grass(self):
        print("\033[42m\033[37m", end = "")

    def end_grass(self):
        print("\033[0m")

    def is_running(self):
        return self.__running.is_set()

    def stop(self):
        self.__running.clear()

    def is_paused(self):
        return self.__paused.is_set()

    def toggle_pause(self):
        if self.__paused.is_set():
            if not self.__game.is_running():
                self.__game.reset()
            self.__paused.clear()
        else:
            self.__paused.set()
