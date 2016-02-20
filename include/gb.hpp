#pragma once

#include "cpu.hpp"
#include "memory.hpp"
#include "opcodes.hpp"

namespace GB {
	extern void reset();
	extern void update();
	extern void updateTimers();
}
