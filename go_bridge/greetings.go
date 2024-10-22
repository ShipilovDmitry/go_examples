package greetings

// TODO here will be Go-wrappers for C-code

// #include "include/add.h"
// #cgo LDFLAGS: -L${SRCDIR}/libs -lgo_bridge -ltrack-filter  -lstdc++
import "C"
import "fmt"

func AddNums() {
    result := C.addNums(2,3)
    fmt.Println(result)
}


func PrintName() {
    C.printName()
}

func GetDistance() {
    result := C.getDistance()
    fmt.Println(result)
}