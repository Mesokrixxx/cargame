#include "error.h"
#include <string.h>
#include <errno.h>

const char *msg = nullptr;

const char *error::get() {
	return msg;
}

void error::set(const char *errMsg) {
	msg = errMsg;
}

void error::setViaErrno() {
	msg = strerror(errno);
}
