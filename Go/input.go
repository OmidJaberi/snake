package main

import (
	"os"
	"syscall"
	"unsafe"
)

func listenForKeyPress(handler func(byte)) {
	buf := make([]byte, 1)
	for {
		os.Stdin.Read(buf)
		handler(buf[0])
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

func restore(fd int, state *syscall.Termios) {
	syscall.Syscall6(syscall.SYS_IOCTL, uintptr(fd),
		uintptr(syscall.TIOCSETA), uintptr(unsafe.Pointer(state)), 0, 0, 0)
}
