#pragma once

#include "util/types.h"

namespace math {

constexpr u64 roundupPow2(u64 n, u64 p) {
	return (n + (p - 1)) & ~(p - 1);
}

}
