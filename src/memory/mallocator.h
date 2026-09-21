#pragma once

#include "memory/allocator.h"

class Mallocator : public Allocator {
public:
	Mallocator() = default;

	u64 used() const override { return _reserved; };
	u64 reserved() const override { return _reserved; };

private:
	void *_allocMemImpl(u64 size) override;
	void _freeMemImpl(void *ptr) override;

	u64 _reserved = 0;
};

extern Mallocator g_mallocator;
