#pragma once

#include <Windows.h>

#include "structs.h"

class CEntity
{
public:
	DWORD64 address;
	int Health = 0;
	int MaxHealth = 0;
	int Shield = 0;
	int MaxSheild = 0;

	int Team = 0;
	Vec3 Pos{ 0, 0, 0 };
	Vec3 CameraPos{ 0, 0, 0 };
	Vec3 ABSVelocity{ 0, 0, 0 };
	Vec2 HeadScreenPos{ 0, 0 };
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

	bool IsTarget(float);
	bool IsVisible(float);
	bool CombatReady();

	int GetBoneFromHitbox(HitboxType hitbox);
	Vec3 GetBonePosition(HitboxType hitbox);
	Vec3 GetBonePositionVector3(HitboxType hitbox);
};
