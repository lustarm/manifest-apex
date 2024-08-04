#include <cstdint>

#include "headers/driver.h"
#include "headers/offsets.h"

void entitythread()
{
	while (true)
	{
		uintptr_t localPlayer = read<uintptr_t>(oBaseAddress + OFF_LOCAL_PLAYER);

	}
}