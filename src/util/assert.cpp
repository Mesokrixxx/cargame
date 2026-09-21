#include "assert.h"
#include <stdlib.h>
#include <stdio.h>

void _assertImpl(SourceLoc loc, bool cond, const char *expr, const char *fmt) {
	if (cond)
		return ;
	fprintf(stderr, "[%s:%d][%s] assertion failed: '%s'\n",
		loc.file(), loc.line(), loc.func(), expr);
	fprintf(stderr, "%s\n", fmt);
	exit(1);
}
