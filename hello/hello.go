package main


// #cgo LDFLAGS: -L. -ladd
// #include "add.h"
import "C"
import (
	"fmt"
	"greetings/greetings"
)

func main() {
    // Get a greeting message and print it.
	result := C.add_nums(2, 3)
	fmt.Println("The result is:", result)
    message := greetings.Hello("Gladys")
    fmt.Println(message)
}