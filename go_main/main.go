package main


import (
	"greetings/go_bridge"
)

// #cgo LDFLAGS: -L. -ltrack-filter -lgo_bridge -lstdc++
import "C"
func main() {
    greetings.Hello()
}
