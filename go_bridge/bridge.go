package bridge

// TODO here will be Go-wrappers for C-code
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!

// #cgo CFLAGS: -I${SRCDIR}/corendk/CoreBridge/include
// #cgo LDFLAGS: -L${SRCDIR}/libs -lgo_bridge -ltrack-filter  -lstdc++
// #include "include/bridge.h"
import "C"
import "unsafe"

func AddNums(num1 int, num2 int) int {
	result := C.addNums(C.int(num1), C.int(num2))
	return int(result)
}

func PrintName() {
	C.printName()
}

func CreateTrackFilter() unsafe.Pointer {
	c_filter := C.createTrackFilter()
	return unsafe.Pointer(c_filter)
}

func DestroyTrackFilter(filter unsafe.Pointer) {
	C.destroyTrackFilter((*C.TrackFilterRef)(filter))
}

func GetTrackInfo(filter unsafe.Pointer) string {
	info := C.getInfo((*C.TrackFilterRef)(filter))
	goString := C.GoString(info)
	C.CStringRelease(info)

	return goString
}
