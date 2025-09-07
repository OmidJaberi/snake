package main

import (
	"fmt"
	"os"
	"syscall"
	"unsafe"
)

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
