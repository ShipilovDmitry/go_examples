package bridge

// TODO here will be Go-wrappers for C-code
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!

// #cgo CFLAGS: -I${SRCDIR}/corendk/CoreBridge/include
// #cgo LDFLAGS: -L${SRCDIR}/libs -lgo_bridge -ltrack-filter -lstdc++
// #include "include/bridge.h"
import "C"
import (
	"fmt"
	"unsafe"
)

type RefsKinds struct {
	Refs  int // Capital letter means public field
	Kinds int
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

func GetIntsSlice() []int {
	c_refs_kinds_vector_interop := C.getIntsArray()

	vector_data := C.vector_data(c_refs_kinds_vector_interop)
	size := C.vector_size(c_refs_kinds_vector_interop)

	elements_amount := int(size) / C.sizeof_int
	// Read the data from memory
	data := make([]int, elements_amount)
	for i := 0; i < elements_amount; i++ {
		data[i] = int(*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(vector_data)) + uintptr(i)*C.sizeof_int)))
	}

	C.vector_destructor(c_refs_kinds_vector_interop)

	return data
}

func GetRefsKinds() []RefsKinds {
	c_refs_kinds_vector_interop := C.getRefsKinds()

	vector_data := C.vector_data(c_refs_kinds_vector_interop)
	size := C.vector_size(c_refs_kinds_vector_interop)

	element_size := unsafe.Sizeof(C.struct_C_RefsKinds{})

	elements_amount := int(size) / int(element_size)
	// Read the data from memory
	data := make([]RefsKinds, elements_amount)
	for i := 0; i < elements_amount; i++ {
		c_ref_kind := (*(*C.struct_C_RefsKinds)(unsafe.Pointer(uintptr(unsafe.Pointer(vector_data)) + uintptr(i)*element_size)))
		data[i].Kinds = int(c_ref_kind.kinds)
		data[i].Refs = int(c_ref_kind.refs)
	}
	fmt.Println(data)

	C.vector_destructor(c_refs_kinds_vector_interop)

	return data
}

func CompareStrings(expected string) bool {
	cString := C.CString(expected)
	stdStringRef := C.std_stringCreate(cString) // memory allocation in C
	defer C.free(unsafe.Pointer(cString))
	data := C.std_stringData(stdStringRef)
	defer C.std_stringDestroy(stdStringRef) // memory deallocation in C
	goString := C.GoString(data)
	return expected == goString
}