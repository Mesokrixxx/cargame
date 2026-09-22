#include "mallocator.h"
#include "util/error.h"
#include "math/util.h"
#include <stdlib.h>

Mallocator g_mallocator;

struct AllocHeader {
	u64 size;
};

constexpr u64 headerSize() {
	return math::roundupPow2(sizeof(AllocHeader), types::maxAlign);
}

void *Mallocator::_allocMemImpl(u64 size) {
	AllocHeader *ptr = (AllocHeader *)malloc(headerSize() + size);
	if (ptr) {
		ptr->size = size;
		_reserved += ptr->size;
	}
	else {
		error::setViaErrno("malloc");
		return nullptr;
	}
	return (u8 *)ptr + headerSize();
}

void Mallocator::_freeMemImpl(void *ptr) {
	AllocHeader *header = (AllocHeader *)((u8 *)ptr - headerSize());

	_reserved -= header->size;
	free(header);
}
