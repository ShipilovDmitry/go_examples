package bridge

//#include "include/bridge.h"
import "C"

func GetDistance() float64 {
    result := C.getDistance()
    return float64(result)
}