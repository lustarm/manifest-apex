#include "headers/driver.h"
#include "headers/map.h"
#include "headers/overlay.h"
#include "headers/entity.h"
#include "headers/aimbot.h"
#include "headers/esp.h"

int main()
{
	std::cout << "[(*)] Loading manifest" << std::endl;

	map_driver();

	while (!hwnd)
	{ hwnd = FindWindowA(NULL, ("Apex Legends")); }
	while (!oPID)
	{ oPID = GetPID("r5apex.exe"); }
	while (!oBaseAddress)
	{ oBaseAddress = GetModuleBaseAddress(oPID, "r5apex.exe"); }

	std::cout << "[(*)] Found apex legends launching manifest" << std::endl;
	/* == Main logic for cheat == */
	_beginthread((_beginthread_proc_type)aimbotthread, 0, 0);
	Sleep(100);
	_beginthread((_beginthread_proc_type)entitythread, 0, 0);
	Sleep(100);
	_beginthread((_beginthread_proc_type)overlaythread, 0, 0);
	// _beginthread((_beginthread_proc_type)espthread, 0, 0);
	Sleep(-1);
	return 0;
}