#pragma once

#include "container/string.h"

void formatType(String& buf, int value);
void formatType(String& buf, u32 value);
void formatType(String& buf, u64 value);
void formatType(String& buf, const char *cstr);
void formatType(String& buf, const u8 *cstr);
void formatType(String& buf, const String& str);

template <u64 N> 
void formatType(String& buf, const char (&cstr)[N]) {
	buf.append(cstr, N - 1);
}

void _formatImpl(String& buf, const char *fmt);

template <typename T, typename ...Rest>
void _formatImpl(String& buf, const char *fmt, const T& current, const Rest ...rest) {
	while (*fmt) {
		if (*fmt == '{' && *(fmt + 1) == '}') {
			formatType(buf, current);
			fmt += 2;
			_formatImpl(buf, fmt, rest...);
			return ;
		}
		buf.append(*fmt++);
	}
}

template <typename ...Args>
String format(Allocator& allocator, const char *fmt, const Args& ...args) {
	String str(allocator, 64);
	
	_formatImpl(str, fmt, args...);
	return str;
}

template <typename ...Args>
String format(const char *fmt, const Args& ...args) {
	return format(g_mallocator, fmt, args...);
}
