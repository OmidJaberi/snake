from random import randint

class SnakeGame:
    def __init__(self, width = 16, height = 16):
        self.__width = width
        self.__height = height
        self.reset()

    def reset(self):
        self.__dir = (0, 1)
        self.__snake = [(int(self.__width / 2), int(self.__height / 2))]
        self.__mouse = (int(self.__width / 2), int(self.__height / 2) + 1)

    def get_width(self):
        return self.__width

    def get_height(self):
        return self.__height

    def on_snake(self, x, y):
        return (x, y) in self.__snake

    def on_mouse(self, x, y):
        return x == self.__mouse[0] and y == self.__mouse[1]

    def spawn(self):
        while self.on_snake(self.__mouse[0], self.__mouse[1]):
            self.__mouse = (randint(0, self.__width - 1), randint(0, self.__height - 1))

    def change_dir(self, x, y):
        self.__dir = (x, y)

    def update(self):
        head = self.__snake[-1]
        new_head = (
            (self.__width + head[0] + self.__dir[0]) % self.__width,
            (self.__height + head[1] + self.__dir[1]) % self.__height
        )
        self.__snake.append(new_head)
        if new_head == self.__mouse:
            self.spawn()
        else:
            self.__snake.pop(0)
        return not new_head in self.__snake[:-1]
