#include "assert.h"
#include "util/log.h"
#include <stdlib.h>

void _assertImpl(SourceLoc loc, bool cond, const char *expr, const char *fmt) {
	if (cond)
		return ;
	_logImpl(loc, stderr, LOG_COLOR_RED "ERR" LOG_COLOR_RST, "assertion failed: '{}'", expr);
	_logImpl(loc, stderr, LOG_COLOR_RED "ERR" LOG_COLOR_RST, "{}", fmt);
	exit(1);
}
