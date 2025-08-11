from random import choice

class SnakeGame:
    def __init__(self, width = 16, height = 16):
        self.__width = width
        self.__height = height
        self.reset()

    def reset(self):
        self.__prev_dir = self.__dir = (0, 1)
        self.__snake = [(int(self.__width / 2), int(self.__height / 2))]
        self.__mouse = (int(self.__width / 2) + self.__dir[0], int(self.__height / 2) + self.__dir[1])

    def get_width(self):
        return self.__width

    def get_height(self):
        return self.__height

    def on_snake(self, x, y):
        return (x, y) in self.__snake

    def on_mouse(self, x, y):
        return x == self.__mouse[0] and y == self.__mouse[1]

    def spawn(self):
        self.__mouse = choice([(x, y) for x in range(self.__width) for y in range(self.__height) if not self.on_snake(x, y)])

    def change_dir(self, x, y):
        if self.__prev_dir == (-x, -y): return
        self.__dir = (x, y)

    def is_running(self):
        return self.__snake[-1] not in self.__snake[:-1]

    def update(self):
        if not self.is_running(): return False
        x, y = self.__snake[-1]
        dx, dy = self.__dir
        new_head = ((x + dx) % self.__width, (y + dy) % self.__height)
        self.__snake.append(new_head)
        if new_head == self.__mouse:
            self.spawn()
        else:
            self.__snake.pop(0)
        self.__prev_dir = self.__dir
        return self.is_running()
