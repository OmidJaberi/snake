import time
import models.snake
import ui.cli

game = models.snake.SnakeGame()
ui = ui.cli.Cli(game)

def key_press_handler(ch):
    if ch == '\x1b' or ch == 'q':
        ui.stop()
    elif ch == ' ':
        ui.toggle_pause()
    elif ch == 'w':
        game.change_dir(-1, 0)
    elif ch == 's':
        game.change_dir(1, 0)
    elif ch == 'd':
        game.change_dir(0, 1)
    elif ch == 'a':
        game.change_dir(0, -1)

def main():
    while ui.is_running():
        if ui.is_paused():
            continue
        ui.draw()
        if not game.update():
            ui.toggle_pause()
            print("Game over!")
        time.sleep(0.2)

if __name__ == "__main__":
    ui.set_key_listener(key_press_handler)
    main()
