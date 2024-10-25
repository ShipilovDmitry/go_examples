package main

import (
	"bridge/go_bridge"
	"testing"
)

// Here we need to put libs of library and bridge manually

func TestBridge(t *testing.T) {
	add_nums_result := bridge.AddNums(2, 3)
	if add_nums_result != 5 {
		t.Errorf("Expected 5, got %d", add_nums_result)
	}
	get_distance_result := bridge.GetDistance()
	if get_distance_result != 42 {
		t.Errorf("Expected 42, got %f", get_distance_result)
	}

	filter := bridge.CreateTrackFilter()
	defer bridge.DestroyTrackFilter(filter)

	info := bridge.GetTrackInfo(filter)
	if info != "TrackFilter" {
		t.Errorf("Expected TrackFilter, got %s", info)
	}

	bridge.PrintName()
}

func TestTypes(t *testing.T) {
	// TODO test creating slice
	bridge.GetRefsKinds()

}
