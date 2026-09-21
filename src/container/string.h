#pragma once

#include "container/dynlist.h"

class String : public Dynlist<char> {
public:
	using Dynlist<char>::Dynlist;
	using Dynlist<char>::set;

	String(const char *str): String(g_mallocator, str) {}
	String(Allocator& allocator, const char *str): String(allocator, str, str ? strlen(str) : 0) {}

	void set(const char *str, u64 n) override;
	void set(const char *str) { set(str, strlen(str)); }

	void append(const char *str) { pushback(str, strlen(str)); }
	void append(const char *str, u64 n) { Dynlist<char>::pushback(str, n); }
	void append(char c) { Dynlist<char>::pushback(c); }
	void append(const String& other) { Dynlist<char>::pushback(other); }

	u64 length() const { return size(); }
	const char *cstr() const { return data(); }

private:
	using Dynlist<char>::data;

	void pushback(const char *str, u64 n) override;
};
