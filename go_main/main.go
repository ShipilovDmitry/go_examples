package main


import (
	"greetings/go_bridge"
)

// Here we need to put libs of library and bridge manually

// #cgo LDFLAGS: -L${SRCDIR}/libs -ltrack-filter -lgo_bridge -lstdc++
import "C"
func main() {
    greetings.Hello()
}
