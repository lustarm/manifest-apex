#include "headers/entity.h"

float entNewVisTime = 0;
float lastbulletspeed=0;
int spectatorcount = 0;
int realspeccount = 0;
DWORD timecountnow = 0;
int timetocountspeczero = 1500;

DWORD64 GetEntityById(int Ent, DWORD64 Base)
{
	DWORD64 EntityList = Base + OFF_ENTITY_LIST; //updated
	DWORD64 BaseEntity = read<DWORD64>(EntityList);
	if (!BaseEntity)
		return NULL;
	return  read<DWORD64>(EntityList + (static_cast<unsigned long long>(Ent) << 5));
}

static uintptr_t GetEntityBoneArray(uintptr_t ent)
{
	return read<uintptr_t>(ent + OFF_BONES);
}

static OW::Vector3 GetEntityBonePosition(uintptr_t ent, uint32_t BoneId, OW::Vector3 BasePosition)
{
	unsigned long long pBoneArray = GetEntityBoneArray(ent);

	OW::Vector3 EntityHead = OW::Vector3();

	EntityHead.X = read<float>(pBoneArray + 0xCC + (BoneId * 0x30)) + BasePosition.X;
	EntityHead.Y = read<float>(pBoneArray + 0xDC + (BoneId * 0x30)) + BasePosition.Y;
	EntityHead.Z = read<float>(pBoneArray + 0xEC + (BoneId * 0x30)) + BasePosition.Z;

	return EntityHead;
}

OW::Vector3 GetEntityBasePosition(uintptr_t ent)
{
	return read<OW::Vector3>(ent + OFF_LOCAL_ORIGIN);
}

bool CEntity::IsTarget() const
{
	float world_time = read<float>(this->address + OFF_TIME_BASE);
	float Time1 = read<float>(this->address + OFF_LAST_AIMEDAT_TIME);
	return (Time1 + 0.2) >= world_time;
}

bool CEntity::IsVisible() const
{
	float world_time = read<float>(this->address + OFF_TIME_BASE);
	float Time1 = read<float>(this->address + OFF_LAST_VISIBLE_TIME);
	return (Time1 + 0.2) >= world_time;
}

bool CEntity::CombatReady()
{
	if (!address) return false;
	if (DyingState) return false;
	if (BleedingOutState) return false;
	if (Health == 0) return false;
	return true;
}

int CEntity::GetBoneFromHitbox(HitboxType hitbox)
{
	uintptr_t ModelPointer = read<uintptr_t>(this->address + OFF_STUDIOHDR);
	if (!(ModelPointer))
		return -1;

	uintptr_t StudioHDR = read<uintptr_t>(ModelPointer + 0x8);
	if (!(StudioHDR))
		return -1;

	auto HitboxCache = read<uint16_t>(StudioHDR + 0x34);
	auto HitboxArray = StudioHDR + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));
	if (!(HitboxArray))
		return -1;

	auto IndexCache = read<uint16_t>(HitboxArray + 0x4);
	auto HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));
	auto BonePointer = HitboxIndex + HitboxArray + (static_cast<int>(hitbox) * 0x20);
	if (!(BonePointer))
		return -1;

	return read<uint16_t>(BonePointer);
}

OW::Vector3 CEntity::GetBonePosition(HitboxType hitbox)
{
	OW::Vector3 Offset = OW::Vector3(0.0f, 0.0f, 0.0f);
	OW::Vector3 OrPosition = this->Pos;
	int Bone = GetBoneFromHitbox(hitbox);
	if (Bone < 0 || Bone > 255)
		return OW::Vector3{ OrPosition.X + Offset.X, OrPosition.Y + Offset.Y ,OrPosition.Z + Offset.Z };

	uintptr_t BonePtr = read<uintptr_t>(this->address + OFF_BONES);
	BonePtr += (Bone * sizeof(Matrix3x4));
	if (!(BonePtr))
		return OW::Vector3{ OrPosition.X + Offset.X, OrPosition.Y + Offset.Y ,OrPosition.Z + Offset.Z };

	Matrix3x4 BoneMatrix = read<Matrix3x4>(BonePtr);
	Vec3 BoneTest = BoneMatrix.GetPosition();
	OW::Vector3 BonePosition = OW::Vector3(BoneTest.X, BoneTest.Y, BoneTest.Z);

	BonePosition = { BonePosition.X + OrPosition.X, BonePosition.Y + OrPosition.Y ,BonePosition.Z + OrPosition.Z };
	return BonePosition;
}

/*
OW::Vector3 CEntity::GetBonePositionVector3(HitboxType hitbox)
{
	// Dont think i need this func
}
*/