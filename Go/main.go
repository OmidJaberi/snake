package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"unsafe"
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

	// Handle Ctrl+C
	c := make(chan os.Signal, 1)
	signal.Notify(c, os.Interrupt)
	go func() {
		<-c
		restore(int(os.Stdin.Fd()), oldState)
		os.Exit(0)
	}()

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
	select {} // Block forever
}

func listenForKeyPress() {
	buf := make([]byte, 1)

	for {
		os.Stdin.Read(buf)
		key := buf[0]

		//fmt.Printf("Key pressed: %v ('%c')\n", key, key)

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
}

func makeRaw(fd int) (*syscall.Termios, error) {
	var oldState syscall.Termios

	// Get current terminal settings
	_, _, errno := syscall.Syscall6(syscall.SYS_IOCTL, uintptr(fd),
		uintptr(syscall.TIOCGETA), uintptr(unsafe.Pointer(&oldState)), 0, 0, 0)
	if errno != 0 {
		return nil, errno
	}

	newState := oldState
	newState.Lflag &^= syscall.ICANON | syscall.ECHO // Turn off canonical mode and echo
	newState.Cc[syscall.VMIN] = 1  // Minimum number of characters for non-canonical read
	newState.Cc[syscall.VTIME] = 0 // Timeout value

	// Set the new settings
	_, _, errno = syscall.Syscall6(syscall.SYS_IOCTL, uintptr(fd),
		uintptr(syscall.TIOCSETA), uintptr(unsafe.Pointer(&newState)), 0, 0, 0)
	if errno != 0 {
		return nil, errno
	}

	return &oldState, nil
}

func restore(fd int, state *syscall.Termios) error {
	_, _, errno := syscall.Syscall6(syscall.SYS_IOCTL, uintptr(fd),
		uintptr(syscall.TIOCSETA), uintptr(unsafe.Pointer(state)), 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}
