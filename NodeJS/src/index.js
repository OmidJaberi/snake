const Snake = require('./Snake');

const stdin = process.stdin;
const stdout = process.stdout;
stdin.setRawMode(true);
stdin.resume();
stdin.setEncoding('utf8');

let game = new Snake(10, 10);
const dir = {
    'w': [-1, 0],
    's': [1, 0],
    'a': [0, -1],
    'd': [0, 1]
}

stdin.on('data', key => {
    if ( key === '\u0003' || key === 'q' ) // ctrl-c or q for exit
        process.exit();
    else if (key == ' ')
        pause();
    else if (dir[key])
        game.changeDir(dir[key]);
});

let interval = null;

function draw(game) {
    console.clear();
    for (let i = 0; i < 2 * game.getWidth() + 2; i++) stdout.write('-');
    stdout.write('\n');
    for (let i = 0; i < game.getHeight(); i++) {
        stdout.write('|');
        for (let j = 0; j < game.getWidth(); j++)
            if (game.onSnake([i, j]))
                stdout.write('o ');
            else if (game.onFood([i, j]))
                stdout.write('# ');
            else
                stdout.write('  ');
        stdout.write(i == parseInt(game.getHeight() / 2) ? `|\tScore: ${game.getScore()}\n` : '|\n');
    }
    for (let i = 0; i < 2 * game.getWidth() + 2; i++) stdout.write('-');
    stdout.write('\n');
}

function pause() {
    if (!game.isRunning()) {
        game = new Snake(10, 10);
        draw(game);
    } else if (interval) {
        console.log("The game is paused.\nPress SPACE to continue.");
        clearInterval(interval);
        interval = null;
    } else {
        interval = setInterval(() => {
            if (game.update())
                draw(game);
            else {
                console.log("Game over!\nPress SPACE to play again.");
                clearInterval(interval);
                interval = null;
            }
        }, 150);
    }
}

draw(game);
console.log("Press SPACE to play/pause...");
