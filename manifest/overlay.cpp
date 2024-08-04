#define IMGUI_DEFINE_MATH_OPERATORS

#include "headers/driver.h"
#include "headers/skCrypt.h"
#include "headers/util.h"
#include "headers/byte_array.h"
#include "headers/etc_elements.h"
#include "headers/nav_elements.h"
#include "headers/config.h"
#include "headers/esp.h"

//namespace fonts
ImFont* medium;
ImFont* bold;
ImFont* tab_icons;
ImFont* logo;
ImFont* tab_title;
ImFont* tab_title_icon;
ImFont* subtab_title;
ImFont* combo_arrow;

enum heads {
    aimbot, visuals, settings
};

enum sub_heads {
    general, accuracy, exploits, _general, advanced
};

/*
static void set_overlay_passthrough(HWND window, bool menu)
{
    if(menu)
        SetWindowLong(window, GWL_EXSTYLE)
}
*/

void overlaythread()
{
	HWND tWnd = FindWindowA(skCrypt("Respawn001"), NULL);

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, random_string_window().c_str(), NULL };
	RegisterClassEx(&wc);
    hwnd = CreateWindow(wc.lpszClassName, random_string_window().c_str(), WS_POPUP, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);

	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
	}

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	SetWindowLong(hwnd, 0, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(tWnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.OversampleH = 5;
    font_config.OversampleV = 5;
    font_config.RasterizerMultiply = 1.2f;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
        0x2DE0, 0x2DFF, // Cyrillic Extended-A
        0xA640, 0xA69F, // Cyrillic Extended-B
        0xE000, 0xE226, // icons
        0,
    };

    font_config.GlyphRanges = ranges;

    medium = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 15.0f, &font_config, ranges);
    bold = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

    tab_icons = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 15.0f, &font_config, ranges);
    logo = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 21.0f, &font_config, ranges);

    tab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 19.0f, &font_config, ranges);
    tab_title_icon = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 18.0f, &font_config, ranges);

    subtab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

    combo_arrow = io.Fonts->AddFontFromMemoryTTF(combo, sizeof(combo), 9.0f, &font_config, ranges);

    // Our state
    ImVec4 clear_color = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    bool Menu = true;
    bool test = false;
    bool done = false;

    while (FindWindowA(skCrypt("Respawn001"), NULL))
    {
        RECT rect;
        GetWindowRect(tWnd, &rect);
		SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_NOZORDER);
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			ImGui::GetIO().MouseDown[0] = true;
		}
		else
		{
			ImGui::GetIO().MouseDown[0] = false;
		}

		if (GetAsyncKeyState(VK_INSERT)) {
			Menu = !Menu;
			//ImGui::GetIO().MouseDrawCursor = Config::Menu;
			Sleep(250);
		}

		if (!Menu && !test) {
			test = true;
			SetFocus(tWnd);
			SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);
		}
		if (Menu && test)
		{
			SetFocus(hwnd);
			ShowCursor(TRUE);
			SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW);
			//UpdateWindow(hwnd);
			//Config::doingentity = 0;
			//Sleep(100);
			//Config::doingentity = 1;
			//_beginthread((_beginthread_proc_type)entity_thread, 0, 0);
			test = false;
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
        if (Menu)
        {
            static heads tab{ aimbot };
            static sub_heads subtab{ general };

            const char* tab_name = tab == aimbot ? "Aimbot" : tab == visuals ? "Visuals" : tab == settings ? "Settings" : 0;
            const char* tab_icon = tab == aimbot ? "B" : tab == visuals ? "D"  : tab == settings ? "E" : 0;

            static bool boolean, boolean_1 = false;
            static int sliderscalar, combo = 0;

            static int aim_key_combo = 0;
			const char* aim_key_type[5] = { "Left Mouse", "Right Mouse",  "Middle Mouse",  "X1 Button",  "X2 Button" };


            const char* combo_items[3] = { "Value", "Value 1", "Value 2" };

            ImGui::SetNextWindowPos(ImVec2{ 50, 30 }, ImGuiCond_Once);
            ImGui::SetNextWindowSize({ 730, 460 });
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

            bool visible = true;

            ImGui::Begin("Apex Manifest", &visible, ImGuiWindowFlags_NoDecoration); 
            {
                auto draw = ImGui::GetWindowDrawList();

                auto pos = ImGui::GetWindowPos();
                auto size = ImGui::GetWindowSize();

                ImGuiStyle style = ImGui::GetStyle();

                draw->AddRectFilled(pos, ImVec2(pos.x + 210, pos.y + size.y), ImColor(24, 24, 26), style.WindowRounding, ImDrawFlags_RoundCornersLeft);
                draw->AddLine(ImVec2(pos.x + 210, pos.y + 2), ImVec2(pos.x + 210, pos.y + size.y - 2), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
                draw->AddLine(ImVec2(pos.x + 47, pos.y + 2), ImVec2(pos.x + 47, pos.y + size.y - 2), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
                draw->AddLine(ImVec2(pos.x + 2, pos.y + 47), ImVec2(pos.x + 47, pos.y + 47), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
                draw->AddLine(ImVec2(pos.x + 63, pos.y + 47), ImVec2(pos.x + 195, pos.y + 47), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
                draw->AddText(logo, 21.0f, ImVec2(pos.x + 14, pos.y + 12), ImColor(147, 190, 66), "A");

                draw->AddText(tab_title_icon, 18.0f, ImVec2(pos.x + 65, pos.y + 14), ImColor(147, 190, 66), tab_icon);
                draw->AddText(tab_title, 19.0f, ImVec2(pos.x + 93, pos.y + 15), ImColor(1.0f, 1.0f, 1.0f), tab_name);

                draw->AddRect(pos + ImVec2(1, 1), pos + size - ImVec2(1, 1), ImColor(1.0f, 1.0f, 1.0f, 0.03f), style.WindowRounding);

                ImGui::SetCursorPos({ 8, 56 });
                ImGui::BeginGroup(); 
                {
                    if (elements::tab("B", tab == aimbot)) { tab = aimbot; }
                    if (elements::tab("D", tab == visuals)) { tab = visuals; }
                    if (elements::tab("E", tab == settings)) { tab = settings; }
                } ImGui::EndGroup();

                switch (tab) {
                case aimbot:
                    draw->AddText(subtab_title, 15.0f, ImVec2(pos.x + 72, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.4f), "MAIN");

                    ImGui::SetCursorPos({ 57, 86 });
                    ImGui::BeginGroup(); 
                    {
                        if (elements::subtab("General", subtab == general)) { subtab = general; }
                        if (elements::subtab("Accuracy", subtab == accuracy)) { subtab = accuracy; }
                        if (elements::subtab("Exploits", subtab == exploits)) { subtab = exploits; }
                    } ImGui::EndGroup();

                    switch (subtab) 
                    {
                    case general:
                        ImGui::SetCursorPos({ 226, 16 });
                        e_elements::begin_child("Aimbot", ImVec2(490, 300)); {
                            ImGui::Checkbox("Enabled", &config::aimbot_enabled);
                            ImGui::Checkbox("Silent aim", &boolean_1);

                            ImGui::SliderInt("Aimbot Smoothing", &config::aim_smoothing, 0, 100, "%d%%", ImGuiSliderFlags_None);

                            ImGui::Combo("Aim Key", &aim_key_combo, aim_key_type, IM_ARRAYSIZE(aim_key_type));
                        }
                        e_elements::end_child();
                        break;

                    case accuracy:
                        ImGui::SetCursorPos({ 226, 16 });
                        e_elements::begin_child("walking thru", ImVec2(240, 300)); {
                            ImGui::Checkbox("Show FOV", &config::show_fov);
                            // ImGui::Checkbox("Toggle 1", &boolean_1);

                            ImGui::SliderInt("FOV", &config::fov, 0, 180, "%d", ImGuiSliderFlags_None);

                            // ImGui::Combo("Combobox", &combo, combo_items, IM_ARRAYSIZE(combo_items));
                        }
                        e_elements::end_child();

                        ImGui::SetCursorPos({ 476, 16 });
                        e_elements::begin_child("the river", ImVec2(240, 240)); {

                        }
                        e_elements::end_child();

                        ImGui::SetCursorPos({ 226, 332 });
                        e_elements::begin_child("water in", ImVec2(240, 114)); {

                        }
                        e_elements::end_child();

                        ImGui::SetCursorPos({ 476, 272 });
                        e_elements::begin_child("my shoes", ImVec2(240, 174)); {

                        }
                        e_elements::end_child();
                        break;
                    }
                    break;
                }
            }
            ImGui::End();
            ImGui::PopStyleVar();
        }
        esp();
        ImGui::EndFrame();
        ImGui::Render();

		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		auto ss = ImVec4(0, 0, 0, 0);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&ss);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		g_pSwapChain->Present(1, 0);
    }

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);
}