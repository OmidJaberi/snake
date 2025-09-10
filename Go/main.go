package main

import (
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
		setMessage("")
		switch game.togglePause() {
		case Paused:
			setMessage("The game is paused. Press SPACE to continue.")
		case GameOver, Win:
			game.init()
		}
	case 'q', 27:
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
			setMessage("Game over! Press SPACE to play again.")
		case Win:
			setMessage("You won! Press SPACE to play again.")
		}
		draw(game)
		time.Sleep(Delay * time.Millisecond)
	}
}
