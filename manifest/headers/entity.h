#pragma once

#include "driver.h"
#include "structs.h"
#include "vector.h"
#include "offsets.h"

extern float entNewVisTime;
extern float lastbulletspeed;
extern int spectatorcount;
extern int realspeccount;
extern DWORD timecountnow;
extern int timetocountspeczero;

class CEntity
{
public:
	DWORD64 address;
	int Health = 0;
	int MaxHealth = 0;
	int Shield = 0;
	int MaxShield = 0;

	int Team = 0;
	OW::Vector3 Pos{ 0, 0, 0 };
	OW::Vector3 CameraPos{ 0, 0, 0 };
	OW::Vector3 ABSVelocity{ 0, 0, 0 };
	OW::Vector3 HeadPos{ 0, 0, 0 };
	OW::Vector2 HeadScreenPos{ 0, 0 };
	std::string Name;

	bool DyingState = false;
	bool BleedingOutState = false;
	bool Visible = false;

	// WTF???
	float AimX = 9999;
	float AimY = 9999;

	uintptr_t WeaponEntity = 0;
	int WeaponIndex = 0;
	float WeaponProjectileSpeed = 0.0f;
	float WeaponProjectileScale = 0.0f;

	bool AimedAt = false;
	bool ZoomedIn = false;

	bool IsTarget(float) const;
	bool IsVisible(float) const;
	bool CombatReady();

	int GetBoneFromHitbox(HitboxType hitbox);
	OW::Vector3 GetBonePosition(HitboxType hitbox);
	// OW::Vector3 GetBonePositionVector3(HitboxType hitbox);
};

OW::Vector3 GetEntityBasePosition(uintptr_t);
void entitythread(void);
