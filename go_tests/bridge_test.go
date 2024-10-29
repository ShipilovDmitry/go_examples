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

func TestIntsArray(t *testing.T) {
	// TODO test creating slice
	expected := []int{1, 2, 3, 4}
	s := bridge.GetIntsSlice()
	for i := 0; i < len(s); i++ {
		if s[i] != expected[i] {
			t.Errorf("Expected %d, got %d", expected[i], s[i])
		}
	}
}

func TestRefsKinds(t *testing.T) {
	refsKindsExpected := []bridge.RefsKinds{
		{Refs: 1, Kinds: 2},
		{Refs: 3, Kinds: 4},
		{Refs: 5, Kinds: 6},
	}
	r := bridge.GetRefsKinds()
	for i := 0; i < len(r); i++ {
		if r[i] != refsKindsExpected[i] {
			t.Errorf("Expected %d, got %d", refsKindsExpected[i], r[i])
		}
	}
}

func TestCompareStrings(t *testing.T) {
	r := bridge.CompareStrings("Hello, world!")
	if r == false {
		t.Errorf("Expected true, got false")
	}
}

func TestPrintIntArray(*testing.T) {
	ints := []int{1, 2, 3, 4}
	bridge.PrintIntArray(ints)
}

func TestPrintRefsKinds(t *testing.T) {
	refsKinds := []bridge.RefsKinds{
		{Refs: 1, Kinds: 2},
		{Refs: 3, Kinds: 4},
		{Refs: 5, Kinds: 6},
	}
	bridge.PrintRefsKinds(refsKinds)
}
