#include <cstdint>

#include "headers/driver.h"
#include "headers/offsets.h"
#include "headers/entity.h"
#include "headers/includes.h"

void entitythread()
{
	while (true)
	{
		LocalEntity.address = read<uintptr_t>(oBaseAddress + OFF_LOCAL_PLAYER);

		if (!LocalEntity.address)
		{
			Entities = {};
			LocalEntity = {};
			continue;
		}

		OW::Vector3 tmp = GetEntityBasePosition(LocalEntity.address);
		LocalEntity.Pos = { tmp.X,tmp.Y,tmp.Z };		// 坐标
		//Vector3 HeadPosition = GetEntityBonePosition(LocalEntity.Address, 8, tmp);
		
		OW::Vector3 HeadPosition = LocalEntity.GetBonePosition(HitboxType::Head);
		
		// Convert to screen position
		int DyingState = read<int>(LocalEntity.address + OFF_LIFE_STATE);
		int Bleedout = read<int>(LocalEntity.address + OFF_BLEEDOUT_STATE);
		// Get screen position
		// Get entity total visible time
		entNewVisTime = read<float>(LocalEntity.address + OFF_LAST_VISIBLE_TIME);
		// Get entity knocked state
		int entKnockedState = read<int>(LocalEntity.address + OFF_BLEEDOUT_STATE);
		// Get player team ID
		// Get entity team ID
		int entTeamID = read<int>(LocalEntity.address + OFF_TEAM_NUMBER);
		// Is it an enemy
		LocalEntity.Health = read<int>(LocalEntity.address + OFF_HEALTH);			// 血量
		LocalEntity.MaxHealth = read<int>(LocalEntity.address + OFF_MAXHEALTH);
		LocalEntity.Shield = read<int>(LocalEntity.address + OFF_SHIELD);
		LocalEntity.MaxShield = read<int>(LocalEntity.address + OFF_MAXSHIELD);
		LocalEntity.ABSVelocity = read<OW::Vector3>(LocalEntity.address + OFF_ABSVELOCITY);
		LocalEntity.ZoomedIn = read<short>(LocalEntity.address + OFF_ZOOMING);
		//printf("%f,%f,%f\n", LocalEntity.AbsVelocity.x, LocalEntity.AbsVelocity.y, LocalEntity.AbsVelocity.z);
		//printf("%d\n", LocalEntity.Health);
		LocalEntity.Team = entTeamID;			// 阵营
		LocalEntity.HeadPos = HeadPosition;// { HeadPosition.x, HeadPosition.y, HeadPosition.z };	// 头部坐标
		LocalEntity.DyingState = DyingState;
		LocalEntity.BleedingOutState = Bleedout;
		if (!LocalEntity.DyingState && !LocalEntity.BleedingOutState) 
		{
			uintptr_t WeaponHandle = read<uintptr_t>(LocalEntity.address + OFF_WEAPON_HANDLE);
			uintptr_t WeaponHandleMasked = WeaponHandle & 0xffff;
			uintptr_t WeaponEntity = read<uintptr_t>(oBaseAddress + OFF_ENTITY_LIST + (WeaponHandleMasked << 5));
			LocalEntity.WeaponEntity = WeaponEntity;
			LocalEntity.WeaponIndex = read<int>(WeaponEntity + OFF_WEAPON_INDEX);
			LocalEntity.WeaponProjectileScale = read<float>(WeaponEntity + OFF_PROJECTILESCALE);
			float bulletspeed= read<float>(WeaponEntity + OFF_PROJECTILESPEED);
			if (bulletspeed != 0) 
			{
				lastbulletspeed = bulletspeed;
			}
			LocalEntity.WeaponProjectileSpeed = lastbulletspeed;
		}
	}
}