#pragma once

#include "util/format.h"
#include "util/sourceloc.h"
#include <stdio.h>

#define LOG_COLOR_RED "\e[31m"
#define LOG_COLOR_YEL "\e[33m"
#define LOG_COLOR_BLU "\e[34m"
#define LOG_COLOR_RST "\e[0m"

#define LOG(fmt, ...) _logImpl(SourceLoc{}, stdout, LOG_COLOR_BLU "LOG" LOG_COLOR_RST, (fmt) __VA_OPT__(,) __VA_ARGS__)
#define WARN(fmt, ...) _logImpl(SourceLoc{}, stdout, LOG_COLOR_YEL "WRN" LOG_COLOR_RST, (fmt) __VA_OPT__(,) __VA_ARGS__)
#define ERROR(fmt, ...) _logImpl(SourceLoc{}, stderr, LOG_COLOR_RED "ERR" LOG_COLOR_RST, (fmt) __VA_OPT__(,) __VA_ARGS__)

void _logImpl(SourceLoc loc, FILE *stream, const char *header, const String& msg);

template <typename ...Args>
void _logImpl(SourceLoc loc, FILE *stream, const char *header, const char *fmt, const Args& ...args) {
	_logImpl(loc, stream, header, format(fmt, args...));	
}
