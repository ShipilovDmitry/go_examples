package bridge

// TODO here will be Go-wrappers for C-code
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!

// #cgo CFLAGS: -I${SRCDIR}/corendk/CoreBridge/include
// #cgo LDFLAGS: -L${SRCDIR}/libs -lgo_bridge -ltrack-filter -lstdc++
// #include "include/bridge.h"
import "C"
import "unsafe"

type RefsKinds struct  {
	refs int
	kinds int
}

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

func GetRefsKinds() []int{
	c_refs_kinds_vector_interop := C.getRefsKinds()

	vector_data := C.vector_data(c_refs_kinds_vector_interop)
	size := C.vector_size(c_refs_kinds_vector_interop)

	elements_amount := int(size) / C.sizeof_int
    // Read the data from memory
    data := make([]int, elements_amount)
    for i := 0; i < elements_amount; i++ {
        data[i] = int(*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(vector_data)) + uintptr(i)*C.sizeof_int)))
    }

	C.vector_destructor(c_refs_kinds_vector_interop)
	
	return nil 
}
