from random import choice

class SnakeGame:
    def __init__(self, width = 15, height = 10):
        self.__width = width
        self.__height = height
        self.reset()

    def reset(self):
        self.__prev_dir = self.__dir = (0, 1)
        x, y = int(self.__height / 2), int(self.__width / 2)
        self.__snake = [(x, y), (x, y)]
        self.spawn()

    def get_width(self):
        return self.__width

    def get_height(self):
        return self.__height

    def get_score(self):
        return 50 * (len(self.__snake) - 2)

    def on_snake(self, x, y):
        return (x, y) in self.__snake

    def on_mouse(self, x, y):
        return x == self.__mouse[0] and y == self.__mouse[1]

    def spawn(self):
        self.__mouse = choice([(x, y) for x in range(self.__height) for y in range(self.__width) if not self.on_snake(x, y)])

    def change_dir(self, x, y):
        self.__dir = self.__dir if self.__prev_dir == (-x, -y) else (x, y)

    def is_running(self):
        return len(self.__snake) <= 2 or self.__snake[-1] not in self.__snake[:-1]

    def update(self):
        if not self.is_running(): return False
        x, y = self.__snake[-1]
        dx, dy = self.__dir
        new_head = ((x + dx) % self.__height, (y + dy) % self.__width)
        self.__snake.append(new_head)
        if new_head == self.__mouse:
            self.spawn()
        else:
            self.__snake.pop(0)
        self.__prev_dir = self.__dir
        return self.is_running()
