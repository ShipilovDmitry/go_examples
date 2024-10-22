package main


import (
	"greetings/go_bridge"
)

// Here we need to put libs of library and bridge manually
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!

// #cgo LDFLAGS: -L${SRCDIR}/libs -lgo_bridge -ltrack-filter  -lstdc++
import "C"
func main() {
    greetings.Hello()
}
