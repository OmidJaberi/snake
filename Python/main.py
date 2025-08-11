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
        if ui.is_paused():
            ui.show_message("The game is paused. Press SPACE to continue.")
    elif ch in ('w', '\x1b[A', '\x1bOA'):
        game.change_dir(-1, 0)
    elif ch in ('s', '\x1b[B', '\x1bOB'):
        game.change_dir(1, 0)
    elif ch in ('d', '\x1b[C', '\x1bOC'):
        game.change_dir(0, 1)
    elif ch in ('a', '\x1b[D', '\x1bOD'):
        game.change_dir(0, -1)

def main():
    ui.show_message("Press SPACE to start the game.\nPress Q to quit.")
    while ui.is_running():
        if ui.is_paused():
            continue
        ui.draw()
        if not game.update():
            ui.toggle_pause()
            ui.show_message("Game over! Press SPACE to play again.")
        time.sleep(0.15)

if __name__ == "__main__":
    ui.set_key_listener(key_press_handler)
    main()
