#include "mallocator.h"
#include "util/error.h"
#include <malloc.h>

Mallocator g_mallocator;

void *Mallocator::_allocMemImpl(u64 size) {
	void *ptr = malloc(size);
	if (ptr)
		_reserved += malloc_usable_size(ptr);
	else
		error::setViaErrno();
	return ptr;
}

void Mallocator::_freeMemImpl(void *ptr) {
	_reserved -= malloc_usable_size(ptr);
	free(ptr);
}
