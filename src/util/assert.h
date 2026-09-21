#pragma once

#include "util/sourceloc.h"
#include "container/string.h"
#include "util/format.h"

#define ASSERT(cond, fmt, ...) \
	_assertImpl(SourceLoc{}, (cond), #cond, (fmt) __VA_OPT__(,) __VA_ARGS__)

void _assertImpl(SourceLoc loc, bool cond, const char *expr, const char *fmt);

template <typename ...Args>
void _assertImpl(SourceLoc loc, bool cond, const char *expr, const char *fmt, const Args& ...args) {
	if (cond)
		return ;
	_assertImpl(loc, cond, expr, format(fmt, args...).cstr());
}
