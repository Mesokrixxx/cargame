#pragma once

#include "util/types.h"

class SourceLoc {
public:
	constexpr SourceLoc(
		const char *f = __builtin_FILE(), 
		u32 l = __builtin_LINE(),
		const char *fn = __builtin_FUNCTION())
		: _file(f), _line(l), _func(fn) {}
	
	constexpr const char *file() const { return _file; }
	constexpr u32 line() const { return _line; };
	constexpr const char *func() const { return _func; }

private:
	const char *_file;
	u32 _line;
	const char *_func;
};
