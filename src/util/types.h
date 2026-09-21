#pragma once

#include <stdint.h>
#include <stddef.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

namespace types {

constexpr u64 maxAlign = alignof(max_align_t);

template <typename T>
static constexpr bool trivially_destructible() {
	return __is_trivially_destructible(T);
}

template <typename T>
static constexpr bool trivially_copyable() {
	return __is_trivially_copyable(T);
}

}
