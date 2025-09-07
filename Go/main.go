package main

import (
	"fmt"
	"os"
	"time"
)

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
		draw()
		time.Sleep(200 * time.Millisecond)
	}
}
