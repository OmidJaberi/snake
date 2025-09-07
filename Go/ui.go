package main

import (
	"fmt"
)

func draw(game *Game) {
	fmt.Print("\033[H\033[2J") // Clear Screen
	for i := 0; i < game.height; i++ {
		for j := 0; j < game.width; j++ {
			if game.onSnake(j, i) {
				fmt.Print("o ")
			} else if game.onFood(j, i) {
				fmt.Print("# ")
			} else {
				fmt.Print(". ")
			}
		}
		fmt.Println()
	}
}
