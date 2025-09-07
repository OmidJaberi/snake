package main

import (
	"fmt"
)

func draw() {
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
}
