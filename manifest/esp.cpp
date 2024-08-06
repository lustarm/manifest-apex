#include "imgui/imgui.h"

#include "headers/structs.h"
#include "headers/entity.h"
#include "headers/util.h"
#include "headers/includes.h"
#include "headers/entitylist.h"
#include "headers/render.h"
#include "headers/vector.h"
#include "headers/render.hpp"
#include "headers/w2s.h"

void esp()
{
	ImDrawList* Draw = ImGui::GetBackgroundDrawList();
	ImVec2 CrossHair = ImVec2(config::screenW / 2.0f, config::screenH / 2.0f);

	if (config::show_fov)
	{
		Draw->AddCircle(CrossHair, config::fov, ImGui::GetColorU32(config::fovcol), 3000, 1.5);
	}

	int spectatorcount = 0;

	if (!Entities.empty()) {
		for (CEntity drawentity : Entities) {
			if (drawentity.address == LocalEntity.address) continue;

			if (config::show_spectators)
			{
				float targetangle = read<float>(drawentity.address + OFF_YAW);
				float targetyaw = -targetangle; // yaw is inverted
				if (targetyaw < 0)
					targetyaw += 360;
				targetyaw += 90; // yaw is off by 90
				if (targetyaw > 360)
					targetyaw -= 360;
				float localangle = read<float>(LocalEntity.address + OFF_YAW);
				float localyaw = -localangle; // yaw is inverted
				if (localyaw < 0)
					localyaw += 360;
				localyaw += 90; // yaw is off by 90
				if (localyaw > 360)
					localyaw -= 360;

				if (targetyaw == localyaw && drawentity.Health == 0)
					spectatorcount++;
			}

			// if (!drawentity.Team && !config::show_teamates_esp) continue;
			if (drawentity.DyingState || drawentity.BleedingOutState) continue;
			if (drawentity.Health == 0) continue;

			OW::Vector3 drawpos = { drawentity.HeadPos.X,drawentity.HeadPos.Y,drawentity.HeadPos.Z };
			OW::Vector3 downpos = drawentity.GetBonePosition(HitboxType::Hip);//GetEntityBonePosition(drawentity.Address, id::hips, GetEntityBasePosition(drawentity.Address));

			float dis = pow(pow(LocalEntity.HeadPos.X - drawentity.HeadPos.X, 2) + pow(LocalEntity.HeadPos.Y - drawentity.HeadPos.Y, 2) + pow(LocalEntity.HeadPos.Z - drawentity.HeadPos.Z, 2), 0.5);
			if (GameUnitsToMeter(dis) < config::esp_distance && !GameUnitsToMeter(dis) < 1)
			{
				if (config::show_healthbar) {
					OW::Vector2 Vec2_A{}, Vec2_B{};
					OW::Vector3 tempVec3 = W2S(m, drawpos);

					if (tempVec3.Z < 0.1f) continue;

					Vec2_A.X = tempVec3.X;
					Vec2_A.Y = tempVec3.Y;

					tempVec3 = W2S(m, downpos);
					Vec2_B.X = tempVec3.X;
					Vec2_B.Y = tempVec3.Y;

					float height = abs(Vec2_A.Y - Vec2_B.Y);
					float width = height * 0.85;
					float Height2 = (abs(Vec2_A.Y - Vec2_B.Y) + 8) * 2;
					OW::Render::DrawSeerLikeHealth(Vec2_A.X, Vec2_A.Y - 30.f, drawentity.Shield, drawentity.MaxShield, drawentity.Health);
				}

				if (config::draw_box)
				{
					OW::Vector2 Vec2_A{}, Vec2_B{};
					OW::Vector3 tempVec3 = W2S(m, drawpos);
					
					if (tempVec3.Z < 0.1f) continue;

					Vec2_A.X = tempVec3.X;
					Vec2_A.Y = tempVec3.Y;

					tempVec3 = W2S(m, downpos);
					Vec2_B.X = tempVec3.X;
					Vec2_B.Y = tempVec3.Y;

					float height = abs(Vec2_A.Y - Vec2_B.Y) * 2;
					float width = height * 0.85;
					ImU32 colorvisbox;
					if (drawentity.Visible) colorvisbox = ImGui::GetColorU32(config::EnemyCol);
					else ImU32 colorvisbox = ImGui::GetColorU32(config::invisEnemyCol);
					OW::Render::DrawCorneredBox(Vec2_A.X - (width / 2) - 1, Vec2_A.Y - (height / 5) - 1, width + 2, height + 12, colorvisbox);
					OW::Render::DrawFilledRect(Vec2_A.X - (width / 2) - 1, Vec2_A.Y - (height / 5) - 1, width + 2, height + 12, ImColor(50, 0, 0, 60));
				}

				if (config::show_esp_distance)
				{
					OW::Vector2 Vec2_A{};
					OW::Vector3 tempVec3 = W2S(m, drawpos);

					if (tempVec3.Z < 0.1f) continue;

					Vec2_A.X = tempVec3.X;
					Vec2_A.Y = tempVec3.Y;

					Vec2_A.Y -= 80;
					std::string disstring = std::to_string((int)GameUnitsToMeter(dis));
					disstring += 'm';
					OW::Render::DrawStrokeText(ImVec2(Vec2_A.X, Vec2_A.Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), (char*)&disstring, 25.f);
				}

				if (config::draw_line)
				{
					OW::Vector2 Vec2_A{}, Vec2_B{};
					OW::Vector3 tempVec3 = W2S(m, drawpos);

					if (tempVec3.Z < 0.1f) continue;

					Vec2_A.X = tempVec3.X;
					Vec2_A.Y = tempVec3.Y;

					Vec2_B = OW::Vector2(config::screenW / 2, config::screenH / 2);
					if (drawentity.Visible) {
						OW::Render::DrawLine(Vec2_A, Vec2_B, OW::Color(204, 51, 51, 255), 2);
					}
					else {
						OW::Render::DrawLine(Vec2_A, Vec2_B, OW::Color(153, 102, 255, 255), 2);
					}
				}

				if (config::draw_bone) 
				{
				    OW::Vector2 Vec2_1{}, Vec2_2{}, Vec2_3{}, Vec2_4{}, Vec2_5{}, Vec2_6{}, Vec2_7{}, Vec2_8{}, Vec2_9{}, Vec2_10{}, Vec2_11{}, Vec2_12{}, Vec2_13{}, Vec2_14{}, Vec2_15{}, Vec2_16{}, Vec2_17{};
				
				    OW::Vector3 tempVec3;
				
				    // Get positions for each bone
				    tempVec3 = W2S(m, drawpos);
				    Vec2_1.X = tempVec3.X;
				    Vec2_1.Y = tempVec3.Y;
				
				    tempVec3 = W2S(m, drawentity.GetBonePosition(HitboxType::Neck));
				    Vec2_2.X = tempVec3.X;
				    Vec2_2.Y = tempVec3.Y;
				
				    tempVec3 = W2S(m, drawentity.GetBonePosition(HitboxType::Stomach));
				    Vec2_3.X = tempVec3.X;
				    Vec2_3.Y = tempVec3.Y;
				
				    tempVec3 = W2S(m, drawentity.GetBonePosition(HitboxType::Hip));
				    Vec2_4.X = tempVec3.X;
				    Vec2_4.Y = tempVec3.Y;
				
				    // Draw bones if entity is visible
				    OW::Color color = drawentity.Visible ? OW::Color(255, 0, 51, 255) : OW::Color(153, 153, 255, 255);
				
				    OW::Render::DrawLine(Vec2_1, Vec2_2, color, 2);
				    OW::Render::DrawLine(Vec2_2, Vec2_3, color, 2);
				    OW::Render::DrawLine(Vec2_3, Vec2_4, color, 2);
				}
			}
		}
	}
}
