#pragma once

#include "../imgui/imgui.h"

namespace config
{
	extern bool show_spectators;

	extern bool aimbot_enabled;
	extern int aim_smoothing;
	extern int aim_key;

	extern int fov;
	extern bool show_fov;
	extern ImVec4 fovcol;

	extern int screenW;
	extern int screenH;

	extern bool show_teamates_esp;
	extern bool show_esp_distance;
	extern bool draw_box;
	extern bool draw_line;
	extern bool show_healthbar;

	extern ImVec4 EnemyCol;
	extern ImVec4 invisEnemyCol;
}
