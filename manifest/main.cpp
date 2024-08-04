#include "headers/driver.h"
#include "headers/map.h"
#include "headers/overlay.h"
#include "headers/entity.h"

int main()
{
	std::cout << "[(*)] Mapping driver to kernel" << std::endl;

	map_driver();

	while (!hwnd)
	{
		std::cout << "[(*)] Finding apex legends..." << std::endl;

		hwnd = FindWindowA(NULL, ("Apex Legends"));
		Sleep(1000);
	}

	while (!oPID)
	{
		std::cout << "[(*)] Finding apex legends procces id..." << std::endl;
		oPID = GetPID("r5apex.exe");
		Sleep(1000);
	}

	while (!oBaseAddress)
	{
		std::cout << "[(*)] Finding base address for apex legends..." << std::endl;
		oBaseAddress = GetModuleBaseAddress(oPID, "r5apex.exe");
		Sleep(1000);
	}

	std::cout << "[(*)] Found apex legends launching manifest" << std::endl;
	/* == Main logic for cheat == */
	_beginthread((_beginthread_proc_type)entitythread, 0, 0);
	_beginthread((_beginthread_proc_type)overlaythread, 0, 0);
	Sleep(-1);
	return 0;
}