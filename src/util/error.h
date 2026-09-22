#pragma once

#include "util/format.h"

namespace error {

const char *get();
void set(const char *cstr);
void set(const String& str);
void set(String&& str);
void setViaErrno(const char *post);

template <typename ...Args>
void set(const char *fmt, const Args& ...args) {
	set(format(fmt, args...));
}

}
