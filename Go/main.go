package main

import (
	"fmt"
	"os"
	"time"
)

var x int = 3
var y int = 3

func main() {
	// Save current settings
	oldState, err := makeRaw(int(os.Stdin.Fd()))
	if err != nil {
		panic(err)
	}
	defer restore(int(os.Stdin.Fd()), oldState)

	// Start a goroutine for keypresses
	go listenForKeyPress()

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
