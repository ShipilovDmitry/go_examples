package main


import (
	"greetings/go_bridge"
)

// Here we need to put libs of library and bridge manually
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!

func main() {
    greetings.AddNums()
	greetings.PrintName()
	greetings.GetDistance()
}
