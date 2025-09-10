package main

import (
	"math/rand"
	"time"
)

type GameState int
const (
	Running GameState = iota
	Paused
	GameOver
	Win
)

type Game struct {
	snake	[][2]int
	food	[2]int
	dir		[2]int
	pDir	[2]int
	width	int
	height	int
	state	GameState
}

func newGame(w, h int) *Game {
	rand.Seed(time.Now().UnixNano())
	game := Game{width: w, height: h}
	game.init()
	return &game
}

func (g *Game) init() {
	g.snake = [][2]int{{g.width / 2, g.height / 2}}
	g.food = [2]int{g.width / 2 + 1, g.height / 2}
	g.dir = [2]int{1, 0}
	g.pDir = g.dir
	g.state = Running
}

func (g *Game) changeDir(x, y int) {
	if g.state != Running { return }
	if !(x + g.dir[0] == 0 && y + g.dir[1] == 0) {
		g.pDir = [2]int{x, y}
	}
}

func (g *Game) spawn() bool {
	emptyCells := make([][2]int, 0, g.width * g.height)
	for i := 0; i < g.width; i++ {
		for j := 0; j < g.height; j++ {
			if !g.onSnake(i, j) && !g.onFood(i, j) {
				emptyCells = append(emptyCells, [2]int{i, j})
			}
		}
	}
	if len(emptyCells) == 0 {
		g.food = [2]int{g.width + 1, g.height + 1}
		return false
	}
	g.food = emptyCells[int(rand.Intn(len(emptyCells)))]
	return true
}

func (g *Game) update() GameState {
	if g.state != Running { return g.state }
	g.dir = g.pDir
	newHead := [2]int{
		(g.snake[len(g.snake) - 1][0] + g.dir[0] + g.width) % g.width,
		(g.snake[len(g.snake) - 1][1] + g.dir[1] + g.height) % g.height,
	}
	if g.onFood(newHead[0], newHead[1]) {
		if !g.spawn() {
			g.state = Win
		}
	} else {
		g.snake = g.snake[1:]
	}
	if g.onSnake(newHead[0], newHead[1]) {
		g.state = GameOver
	}
	g.snake = append(g.snake, newHead)
	return g.state
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

func (g *Game) getScore() int {
	return (len(g.snake) - 2) * 50
}

func (g *Game) togglePause() GameState {
	if g.state == Running {
		g.state = Paused
	} else if g.state == Paused {
		g.state = Running
	}
	return g.state
}
