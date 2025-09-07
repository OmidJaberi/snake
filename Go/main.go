package main

import (
	"fmt"
	"os"
	"time"
)

var game *Game

func keyPressHandler(key byte) {
	if key == 'a' {
		game.changeDir(-1, 0)
	} else if key == 'd' {
		game.changeDir(1, 0)
	} else if key == 'w' {
		game.changeDir(0, -1)
	} else if key == 's' {
		game.changeDir(0, 1)
	} else if key == 27 || key == 'q' { // Exit on ESC or Q
		fmt.Println("Exiting...")
		os.Exit(0)
	}
}

func main() {
	game = newGame(12, 8)
	// Set Terminal settings
	oldState, err := makeRaw(int(os.Stdin.Fd()))
	if err != nil {
		panic(err)
	}
	defer restore(int(os.Stdin.Fd()), oldState)

	// Goroutine for keypress
	go listenForKeyPress(keyPressHandler)

	// Main thread
	for {
		draw(game)
		game.update()
		time.Sleep(200 * time.Millisecond)
	}
}
