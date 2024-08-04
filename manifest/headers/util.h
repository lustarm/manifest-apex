#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <string>
#include <time.h>
#include <d3d11.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

#include "headers/skCrypt.h"
#include "headers/structs.h"

#pragma comment(lib, "d3d11.lib")

constexpr auto M_PI = 3.14159265358979323846f;
constexpr auto M_RADPI = 57.295779513082f;
#define M_PI_F        ((float)(M_PI))
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define ANGLE2SHORT(x) ((int)((x)*65536/360) & 65535)
#define SHORT2ANGLE(x)    ((x)*(360.0/65536))

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern IDXGISwapChain* g_pSwapChain;
extern ID3D11RenderTargetView* g_mainRenderTargetView;


std::string random_string_window();

void CleanupRenderTarget();
void CleanupDeviceD3D();
void CreateRenderTarget();
bool CreateDeviceD3D(HWND hWnd);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

float MeterToGameUnits(float);
float GameUnitsToMeter(float);
