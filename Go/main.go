package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"unsafe"
)

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
	fmt.Println("Press ESC to quit...")
	select {} // Block forever
}

func listenForKeyPress() {
	buf := make([]byte, 1)

	for {
		os.Stdin.Read(buf)
		key := buf[0]

		fmt.Printf("Key pressed: %v ('%c')\n", key, key)

		if key == 27 { // Exit on ESC
			fmt.Println("ESC pressed. Exiting...")
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
