package greetings

// TODO here will be Go-wrappers for C-code
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!

// #include "include/add.h"
// #cgo LDFLAGS: -L${SRCDIR}/libs -lgo_bridge -ltrack-filter  -lstdc++
import "C"

func AddNums(num1 int, num2 int) int {
    result := C.addNums(C.int(num1), C.int(num2))
    return int(result)
}

func PrintName() {
    C.printName()
}

func GetDistance() float64 {
    result := C.getDistance()
    return float64(result)
}
