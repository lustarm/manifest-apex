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

	extern float esp_distance;
	extern bool show_teamates_esp;
	extern bool show_esp_distance;
	extern bool draw_bone;
	extern bool draw_box;
	extern bool draw_line;
	extern bool show_healthbar;

	extern bool TargetTeamates;
	
	extern bool NoRecoil;
	extern bool NoSpread;

	extern float SmoothAmount;
	extern float ZoomedSmoothAmount;

	extern bool Trigger;

	extern int Bone;
	extern bool AutoBone;

	extern bool Prediction;

	extern int IntervalTime;
	extern int TriggerTime;

	extern float RecoilNumX;
	extern float RecoilNumY;

	extern bool TriggeredIsZoom;

	extern bool dianshe;

	extern ImVec4 EnemyCol;
	extern ImVec4 invisEnemyCol;
}
