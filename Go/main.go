package main

import (
	"fmt"
	"os"
	"time"
)

var x int = 3
var y int = 3

func keyPressHandler(key byte) {
	if key == 'a' && x > 0 {
		x--
	} else if key == 'd' && x < 6 {
		x++
	} else if key == 'w' && y > 0 {
		y--
	} else if key == 's' && y < 6 {
		y++
	} else if key == 27 || key == 'q' { // Exit on ESC or Q
		fmt.Println("Exiting...")
		os.Exit(0)
	}
}

func main() {
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
		fmt.Print("\033[H\033[2J") // Clear Screen
		for i := 0; i < 7; i++ {
			for j := 0; j < 7; j++ {
				if i == y && j == x {
					fmt.Print("o ")
				} else {
					fmt.Print(". ")
				}
			}
			fmt.Println()
		}
		time.Sleep(200 * time.Millisecond)
	}
}
