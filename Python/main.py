import sys
import tty
import termios
import threading
import time
import select

paused = threading.Event()
paused.clear()
running = True

def key_listener():
    global running
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
                elif ch == '\x1b':
                    running = False
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

def main():
    global running
    i = 0
    while running:
        if not paused.is_set():
            print(i)
            i += 1
        time.sleep(0.5)

if __name__ == "__main__":
    listener_thread = threading.Thread(target=key_listener, daemon=True)
    listener_thread.start()

    main()

