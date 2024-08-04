#include "headers/structs.h"

Vec3 Matrix3x4::GetPosition() {
	return Vec3{ matrix[0][3], matrix[1][3], matrix[2][3] };
}

Vec3 Matrix3x4::GetPosition2() {
	return Vec3{ matrix[0][3], matrix[1][3], matrix[2][3] };
}
