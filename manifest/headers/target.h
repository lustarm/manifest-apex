#pragma once

#include "util.h"
#include "vector.h"
#include "config.h"

#include <complex>
#include <algorithm>

QAngle CalculateAngle(Vec3 from, OW::Vector3 to);
QAngle SmoothLinear(QAngle LocalAngle, QAngle TargetAngle, float speed);

// OW::Vector3 W2S(MatrixArray matrix, OW::Vector3 Position);
struct OW::Vector3 _WorldToScreen(const struct OW::Vector3 pos, struct MatrixArray matrix);

void AimCorrection(OW::Vector3 LocalPos, float scale1, OW::Vector3* InVecArg, OW::Vector3 currVelocity, float Bulletspeed);

