#include "string.h"

void String::set(const char *str, u64 n) {
	clear();
	reserve(n + 1);
	_copyDataImpl(data(), str, n);
	data()[n] = 0;
	setSize(n);
}

void String::pushback(const char *str, u64 n) {
	reserve(size() + n + 1);
	_copyDataImpl(data() + size(), str, n);
	data()[size() + n] = 0;
	setSize(size() + n);
}
