package main

import (
	"greetings/go_bridge"
	"testing"
)

// Here we need to put libs of library and bridge manually
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!


func TestBridge(t *testing.T) {
	add_nums_result := greetings.AddNums(2, 3)
	if add_nums_result != 5 {
		t.Errorf("Expected 5, got %d", add_nums_result)
	}
	get_distance_result := greetings.GetDistance()
	if get_distance_result != 42 {
		t.Errorf("Expected 42, got %f", get_distance_result)
	}

	greetings.PrintName()
}
