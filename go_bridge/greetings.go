package greetings

// TODO here will be Go-wrappers for C-code

// #include "include/add.h"
import "C"
import "fmt"
func Hello() {
    result := C.add_nums(2,3)
    fmt.Println(result)
}
