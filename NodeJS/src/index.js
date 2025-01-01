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

console.log("Press SPACE to play/pause...");
let interval = null, i = 0;

function pause() {
    if (interval) {
        clearInterval(interval);
        interval = null;
    } else {
        interval = setInterval(() => {
            console.log(i);
            i++;
        }, 1000);
    }
}
