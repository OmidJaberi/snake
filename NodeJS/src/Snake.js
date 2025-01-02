class Snake {
    #snake
    #food
    #dir
    #width
    #height
    #running
    constructor(width, height) {
        this.#width = width;
        this.#height = height;
        this.#snake = [[height / 2, width / 2], [height / 2, width / 2]];
        this.#dir = [0, 1];
        this.#food = null;
        this.#running = true;
        this.spawnFood();
    }
    update() {
        if (!this.#running) return false;
        let newHead = [
            (this.getHeight() + this.#dir[0] + this.#snake[0][0]) % this.getHeight(),
            (this.getWidth() + this.#dir[1] + this.#snake[0][1]) % this.getWidth()
        ];
        if (!this.onFood(newHead))
            this.#snake.pop();
        if (this.onSnake(newHead)) {
            this.#running = false;
            return false;
        }
        this.#snake.unshift(newHead);
        if (this.onFood(newHead))
            this.spawnFood();
        return true;
    }
    changeDir(dir) {
        if (!this.#running) return;
        this.#dir = dir;
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
        if (!this.#running) return;
        console.log("MEME");
        let free = [];
        for (let x = 0; x < this.getHeight(); x++)
            for (let y = 0; y < this.getWidth(); y++) {
                if (!this.onSnake([x, y]))
                    free.push([x, y]);
            }
        this.#food = free[Math.floor(Math.random() * free.length)];
    }
    getScore() { return this.#snake.length - 2; }
    getWidth() { return this.#width; }
    getHeight() { return this.#height; }
}

module.exports = Snake;

