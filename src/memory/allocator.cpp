#include "allocator.h"
#include "util/assert.h"

void *Allocator::allocMem(u64 size) {
	void *ptr = _allocMemImpl(size);
	ASSERT(ptr, 
		"allocation failed");
	
	_allocs++;
	return ptr;
}

void Allocator::freeMem(void *ptr) {
	if (!ptr)
		return ;
	_freeMemImpl(ptr);
	_frees++;
}
