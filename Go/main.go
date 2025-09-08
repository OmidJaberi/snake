package main

import (
	"fmt"
	"os"
	"time"
)

const (
	Delay = 200
	Width = 12
	Height = 8
)

var game *Game = newGame(Width, Height)

func keyPressHandler(key byte) {
	switch key {
	case 'a':
		game.changeDir(-1, 0)
	case 'd':
		game.changeDir(1, 0)
	case 'w':
		game.changeDir(0, -1)
	case 's':
		game.changeDir(0, 1)
	case 'q', 27:
		fmt.Println("Exiting...")
		os.Exit(0)
	}
}

func main() {
	oldState, err := makeRaw(int(os.Stdin.Fd()))
	if err != nil { panic(err) }
	defer restore(int(os.Stdin.Fd()), oldState)

	go listenForKeyPress(keyPressHandler)
	for {
		game.update()
		draw(game)
		time.Sleep(Delay * time.Millisecond)
	}
}
