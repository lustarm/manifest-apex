#include "headers/config.h"
#include "headers/entity.h"
#include "headers/includes.h"
#include "headers/structs.h"
#include "headers/vector.h"
#include "headers/target.h"
#include "headers/w2s.h"

using namespace OW;

static auto NewAngle = QAngle{ 0,0};
static auto PreviousAngle = QAngle{ 0,0};

CEntity AimEntity = {};

void aimbotthread() 
{
	float crosshairX = config::screenW / 2.f;
	float crosshairY = config::screenH / 2.f;

	QAngle AimingAngle = { 0,0 };
	Vector3 HeadPosition1 = { 0,0,0 };

	uint64_t viewRenderer = read<uint64_t>(oBaseAddress + OFF_VIEWRENDER);

	while (true) 
	{
		if (!LocalEntity.address || Entities.empty()) continue;

		m = read<MatrixArray>(read<uint64_t>(viewRenderer + OFF_VIEWMATRIX));

		OW::Vector3 HeadPosition = { 0,0,0 };

		float closestX = 9999;
		float closestY = 9999;
		bool InFov = false;

		Vector3 w2sHeadAimPos;

		for (CEntity ce : Entities) 
		{
			if (ce.address == LocalEntity.address) continue;

			float dis = (float)pow(pow(LocalEntity.HeadPos.X - ce.HeadPos.X, 2) + pow(LocalEntity.HeadPos.Y - ce.HeadPos.Y, 2) + pow(LocalEntity.HeadPos.Z - ce.HeadPos.Z, 2), 0.5);
			if (GameUnitsToMeter(dis) > config::esp_distance) continue;

			if (config::Bone == 0 || config::AutoBone) HeadPosition = ce.GetBonePosition(HitboxType::Head);
			else if(config::Bone == 1) HeadPosition = ce.GetBonePosition(HitboxType::Neck);
			else if (config::Bone == 2) HeadPosition = ce.GetBonePosition(HitboxType::Stomach);
			else if (config::Bone == 3) HeadPosition = ce.GetBonePosition(HitboxType::Hip);

			// Convert to screen position
			Vector3 PreditPos = HeadPosition;

			if (config::Prediction) 
			{
				ce.ABSVelocity = read<Vector3>(ce.address + OFF_ABSVELOCITY);
				AimCorrection(LocalEntity.HeadPos, LocalEntity.WeaponProjectileScale, &PreditPos, OW::Vector3(ce.ABSVelocity.X, ce.ABSVelocity.Y, ce.ABSVelocity.Z), LocalEntity.WeaponProjectileSpeed);
				w2sHeadAimPos = W2S(m, PreditPos);
			}
			else
			{
				w2sHeadAimPos = W2S(m, HeadPosition);
			}

			float entX = w2sHeadAimPos.X;
			float entY = w2sHeadAimPos.Y;

			if (ce.Visible && !ce.DyingState && !ce.BleedingOutState)
			{
				// Aimbot fov
				if (abs(crosshairX - entX) < abs(crosshairX - closestX) && sqrt(pow((crosshairX - entX), 2) + pow((crosshairY - entY), 2)) < config::fov)
				{
					// Aimbot find closest target
					closestX = entX;
					closestY = entY;
					AimEntity = ce;
					AimEntity.AimX = entX;
					AimEntity.AimY = entY;

					// If enemy is in fov set to true
					InFov = true;
					HeadPosition1 = PreditPos;
				}
			}
		}
	
		if (config::aimbot_enabled && GetAsyncKeyState(config::aim_key) 
		    && InFov && !LocalEntity.DyingState && !LocalEntity.BleedingOutState)
		{
		
		    // Ensure cursor info is valid
		    CURSORINFO ci = { sizeof(CURSORINFO) };
			if (!GetCursorInfo(&ci))
				continue;
			if (ci.flags != 0)
				continue;

			aX = (closestX - crosshairX) / (config::SmoothAmount / 10.0f);
			aY = (closestY - crosshairY) / (config::SmoothAmount / 10.0f);
			// Move the mouse
			mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(aX), static_cast<DWORD>(aY), 0, 0);

		}

		if (config::NoRecoil && LocalEntity.Health > 0)
		{
			auto PunchWeapon = read<QAngle>(LocalEntity.address + OFF_PUNCH_ANGLES);
			auto viewAngles1 = read <QAngle>(LocalEntity.address + OFF_VIEW_ANGLES);

			NewAngle.x = viewAngles1.x + ((PreviousAngle.x - PunchWeapon.x) * (config::RecoilNumX / 100.f));
			NewAngle.y = viewAngles1.y + ((PreviousAngle.y - PunchWeapon.y) * (config::RecoilNumY / 100.f));

			if (NewAngle.x != viewAngles1.x || NewAngle.y != viewAngles1.y)
				write<QAngle>(LocalEntity.address + OFF_VIEW_ANGLES, NewAngle);

			PreviousAngle = PunchWeapon;
		}
	}
}