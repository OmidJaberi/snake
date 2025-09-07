package main

import (
	"fmt"
	"math/rand"
	"time"
)

type Game struct {
	snake	[][2]int
	food	[2]int
	dir		[2]int
	width	int
	height	int
	running	bool
}

func newGame(w, h int) *Game {
	rand.Seed(time.Now().UnixNano())
	game := Game{width: w, height: h}
	game.init()
	return &game
}

func (g *Game) init() {
	fmt.Println("Inited")
	g.snake = [][2]int{{g.width / 2, g.height / 2}}
	g.dir = [2]int{0, 1}
	g.spawn()
}

func (g *Game) changeDir(x, y int) {
	if !(x + g.dir[0] == 0 && y + g.dir[1] == 0) {
		g.dir = [2]int{x, y}
	}
}

func (g *Game) spawn() {
	x := rand.Intn(g.width)
	y := rand.Intn(g.height)
	g.food = [2]int{x, y}
}

func (g *Game) update() {
	new_head := [2]int{
		(g.snake[len(g.snake) - 1][0] + g.dir[0] + g.width) % g.width,
		(g.snake[len(g.snake) - 1][1] + g.dir[1] + g.height) % g.height,
	}
	g.snake = append(g.snake, new_head)
	if g.onFood(new_head[0], new_head[1]) {
		g.spawn()
	} else {
		g.snake = g.snake[1:]
	}
}

func (g *Game) onSnake(x, y int) bool {
	for _, cell := range g.snake {
		if cell[0] == x && cell[1] == y {
			return true
		}
	}
	return false
}


func (g *Game) onFood(x, y int) bool {
	return (x == g.food[0] && y == g.food[1])
}
