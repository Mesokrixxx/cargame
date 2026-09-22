#pragma once

#include "util/sourceloc.h"

namespace error {

const char *get();
void set(const char *errMsg);
void setViaErrno();

}
