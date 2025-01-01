class Snake {
    #snake
    #food
    #dir
    #width
    #height
    constructor(width, height) {
        this.#width = width;
        this.#height = height;
        this.#snake = [[height / 2, width / 2]];
        this.#dir = [0, 1];
        this.#food = null;
        this.spawnFood();
    }
    update() {}
    changeDir(dir) {
        this.dir = dir;
    }
    onSnake([x, y]) {
        let ans = false;
        this.#snake.forEach(cell => {
            ans = ans || (x === cell[0] && y === cell[1]);
        });
        return ans;
    }
    onFood([x, y]) {
        return this.#food && (x === this.#food[0] && y === this.#food[1]);
    }
    spawnFood() {
        console.log("MEME");
        let free = [];
        for (let x = 0; x < this.getHeight(); x++)
            for (let y = 0; y < this.getWidth(); y++) {
                if (!this.onSnake([x, y]))
                    free.push([x, y]);
            }
        this.#food = free[Math.floor(Math.random() * free.length)];
    }
    getScore() { return this.#snake.length; }
    getWidth() { return this.#width; }
    getHeight() { return this.#height; }
}

module.exports = Snake;

