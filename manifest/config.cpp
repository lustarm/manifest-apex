#include "headers/config.h"

namespace config
{
	bool show_spectators = false;

	bool aimbot_enabled = false;
	int aim_smoothing = 0;
	int aim_key = 6;

	int fov = 180;
	bool show_fov = true;
	ImVec4 fovcol = ImVec4(1.0f, 0.9f, 0, 1);

	int screenW = 1920;
	int screenH = 1080;

	bool show_teamates_esp = false;
	bool show_esp_distance = false;
	bool draw_box = false;
	bool draw_line = false;
	bool show_healthbar = false;

	ImVec4 EnemyCol = ImVec4(1, 0.f, 0.4f, 1);
	ImVec4 invisEnemyCol = ImVec4(0.8f, 0, 1.f, 1);
}