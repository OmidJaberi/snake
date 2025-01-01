const Snake = require('./Snake');

const stdin = process.stdin;
const stdout = process.stdout;
stdin.setRawMode(true);
stdin.resume();
stdin.setEncoding('utf8');

stdin.on('data', key => {
    if ( key === '\u0003' || key === 'q' ) // ctrl-c or q for exit
        process.exit();
    else if (key == ' ')
        pause();
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
    if (interval) {
        clearInterval(interval);
        interval = null;
    } else {
        interval = setInterval(() => {
            game.update();
            draw(game);
        }, 150);
    }
}

const game = new Snake(10, 10);
draw(game);
console.log("Press SPACE to play/pause...");
