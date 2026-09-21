#include "log.h"

void _logImpl(SourceLoc loc, FILE *stream, const char *header, const String& msg) {
	fprintf(stream, "[%s][%s:%d][%s] %s%s",
		header, loc.file(), loc.line(), loc.func(),
		msg.cstr(), msg.size () ? (msg[msg.size() - 1] != '\n' ? "\n" : "") : "\n");
}
