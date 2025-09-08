package main

import (
	"fmt"
)

const (
	Snake = "🔵"
	Food = "🍎"
	Grass = "  "
)

func draw(game *Game) {
	fmt.Print("\033[H\033[2J") // Clear Screen
	setGrass()
    fmt.Print("╔")
	for i := 0; i < 2 * game.width; i++ {
        fmt.Printf("═")
	}
    fmt.Println("╗")
	for i := 0; i < game.height; i++ {
        fmt.Print("║");
		for j := 0; j < game.width; j++ {
			if game.onSnake(j, i) {
				fmt.Print(Snake)
			} else if game.onFood(j, i) {
				fmt.Print(Food)
			} else {
				fmt.Print(Grass)
			}
		}
        fmt.Println("║");
	}
    fmt.Print("╚")
	for i := 0; i < 2 * game.width; i++ {
        fmt.Printf("═")
	}
    fmt.Println("╝")
	setDefault()
}

func setGrass() {
	fmt.Print("\033[42m\033[37m")
}

func setDefault() {
	fmt.Print("\033[0m")
}
