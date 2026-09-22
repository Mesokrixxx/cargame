#include "error.h"
#include "util/format.h"
#include <errno.h>

String msg(512);

const char *error::get() {
	return msg.cstr();
}

void error::set(const char *cstr) {
	msg = cstr;
}

void error::set(const String& str) {
	msg = str;
}

void error::set(String&& str) {
	msg = (String&&)str;
}

void error::setViaErrno(const char *post) {
	format(msg, "{}{}{}", post ? post : "", post ? ": " : "", strerror(errno));
}
