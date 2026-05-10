#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include "memtypes.h"

#define void_errno void
#define type_errno(type) type

#define void_stop void

// non_call_return for after void_stop non checkers target return
#define non_call_return return

#define null NULL

#define take
