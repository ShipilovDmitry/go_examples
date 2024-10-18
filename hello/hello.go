package main


import (
	"greetings/greetings"
)

// #cgo LDFLAGS: -L. -ladd -lstdc++
import "C"
func main() {
    greetings.Hello()
}
