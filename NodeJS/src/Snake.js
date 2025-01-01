class Snake {
    constructor(width, height) {
        this.width = width;
        this.height = height;
        this.snake = [[height / 2, width / 2]];
        this.dir = [0, 1];
        this.food = null;
        this.spawnFood;
    }
    update() {}
    changeDir(dir) {
        this.dir = dir;
    }
    spawnFood() {}
}

module.exports = Snake;

