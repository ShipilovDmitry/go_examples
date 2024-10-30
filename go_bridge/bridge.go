package bridge

// TODO here will be Go-wrappers for C-code
// WARNING the order of linking libraries metters! -lgo_bridge should be the first one!

// #cgo CFLAGS: -I${SRCDIR}/corendk/CoreBridge/include
// #cgo LDFLAGS: -L${SRCDIR}/libs -lgo_bridge -ltrack-filter -lstdc++
// #include "include/bridge.h"
// #include "include/callbacks.h"
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

func PrintIntArray(expected []int) {
	cArray := (*C.int)(C.malloc(C.size_t(len(expected)) * C.sizeof_int))
	defer C.free(unsafe.Pointer(cArray))
	for i, v := range expected {
		*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(cArray)) + uintptr(i)*C.sizeof_int)) = C.int(v)
	}
	C.ints_array((*C.uchar)(unsafe.Pointer(cArray)), C.size_t(len(expected)))
}

func PrintRefsKinds(refsKinds []RefsKinds) {
	arrayLength := unsafe.Sizeof(C.struct_C_RefsKinds{}) * uintptr(len(refsKinds))
	cArray := (*C.struct_C_RefsKinds)(C.malloc(C.size_t(arrayLength)))
	defer C.free(unsafe.Pointer(cArray))
	for i, v := range refsKinds {
		*(*C.struct_C_RefsKinds)(unsafe.Pointer(uintptr(unsafe.Pointer(cArray)) + uintptr(i)*unsafe.Sizeof(C.struct_C_RefsKinds{}))) = C.struct_C_RefsKinds{
			refs:  C.int(v.Refs),
			kinds: C.int(v.Kinds),
		}
	}
	C.refs_kinds_array((*C.uchar)(unsafe.Pointer(cArray)), C.size_t(len(refsKinds)))
}

//export go_callback_1
func go_callback_1() {
	fmt.Println("Go callback called")
}

//export go_callback_2
func go_callback_2() {
	fmt.Println("Go callback 2")
}

func GoFunctionInC() {
	C.get_go_callback((*[0]byte)(C.go_callback_2))
}
