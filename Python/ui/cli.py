def draw(game):
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
