#pragma once

#include "util/types.h"

inline void *operator new(u64, void *ptr) { return ptr; }

class Allocator {
public:
	Allocator() = default;
	Allocator(const Allocator& other) = delete;
	Allocator& operator=(const Allocator& other) = delete;
	virtual ~Allocator() = default;

	void *allocMem(u64 size);
	void freeMem(void *ptr);

	u64 allocs() const { return _allocs; }
	u64 frees() const { return _frees; }

	virtual u64 used() const = 0;
	virtual u64 reserved() const = 0;

protected:
	virtual void *_allocMemImpl(u64 size) = 0;
	virtual void _freeMemImpl(void *ptr) = 0;

private:
	u64 _allocs = 0;
	u64 _frees = 0;
};
