#include <Windows.h>

#include "headers/config.h"

namespace config
{
	bool show_spectators = false;

	bool aimbot_enabled = true;
	// int aim_smoothing = 0;
	int aim_key = VK_XBUTTON2;

	int fov = 180;
	bool show_fov = true;
	ImVec4 fovcol = ImVec4(1.0f, 0.9f, 0, 1);

	int screenW = 1920;
	int screenH = 1080;

	float esp_distance = 300.0f;
	bool show_teamates_esp = false;
	bool show_esp_distance = true;
	bool draw_box = true;
	bool draw_line = false;
	bool draw_bone = false;
	bool show_healthbar = false;

	bool TargetTeamates = true;

	float SmoothAmount = 10.0f;
	float ZoomedSmoothAmount = 1.0f;

	bool NoRecoil = true;
	float RecoilNumX = 100.0f;
	float RecoilNumY = 100.0f;

	bool NoSpread = true;

	int Bone = 0;
	bool AutoBone = false;

	int IntervalTime = 500;
	int TriggerTime = 200;

	bool Prediction = false;

	ImVec4 EnemyCol = ImVec4(1, 0.f, 0.4f, 1);
	ImVec4 invisEnemyCol = ImVec4(0.8f, 0, 1.f, 1);
}