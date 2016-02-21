#pragma once

#include "cpu.hpp"
#include "memory.hpp"
#include "opcodes.hpp"
#include "gpu.hpp"

namespace GB {
	extern void reset();
	extern void update();
	extern void updateTimers();
}
