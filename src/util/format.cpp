#include "format.h"
#include <stdio.h>

void formatType(String& buf, int value) {
	char tmp[32];

	int len = snprintf(tmp, sizeof(tmp), "%d", value);
	buf.append(tmp, len);
}

void formatType(String& buf, u32 value) {
	char tmp[32];

	int len = snprintf(tmp, sizeof(tmp), "%u", value);
	buf.append(tmp, len);
}

void formatType(String& buf, u64 value) {
	char tmp[64];

	int len = snprintf(tmp, sizeof(tmp), "%zu", value);
	buf.append(tmp, len);
}

void formatType(String& buf, const char *cstr) {
	if (!cstr) {
		formatType(buf, "(null)");
		return ;
	}
	buf.append(cstr, strlen(cstr));
}

void formatType(String& buf, const u8 *cstr) {
	formatType(buf, (const char *)cstr);
}

void formatType(String& buf, const String& str) {
	buf.append(str);
}

void _formatImpl(String& buf, const char *fmt) {
	buf.append(fmt);
}
