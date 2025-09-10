package main

import (
	"fmt"
	"os"
	"time"
)

const (
	Delay = 150
	Width = 15
	Height = 10
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
	case ' ':
		if game.togglePause() {
			setMessage("The game is paused. Press SPACE to continue.")
		} else {
			setMessage("")
		}
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
		switch game.update() {
		case GameOver:
			fmt.Println("Game over!!!")
			os.Exit(0)	
		case Win:
			fmt.Println("You won!!!")
			os.Exit(0)	
		}
		draw(game)
		time.Sleep(Delay * time.Millisecond)
	}
}
