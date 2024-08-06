#include "headers/w2s.h"

OW::Vector3 W2S(MatrixArray matrix, OW::Vector3 pos)
{
	struct OW::Vector3 out;

	float _x = matrix.matrix[0] * pos.X + matrix.matrix[1] * pos.Y + matrix.matrix[2] * pos.Z + matrix.matrix[3];
	float _y = matrix.matrix[4] * pos.X + matrix.matrix[5] * pos.Y + matrix.matrix[6] * pos.Z + matrix.matrix[7];

	out.Z = matrix.matrix[12] * pos.X + matrix.matrix[13] * pos.Y + matrix.matrix[14] * pos.Z + matrix.matrix[15];

	_x *= 1.f / out.Z;
	_y *= 1.f / out.Z;

	out.X = config::screenW * .5f;
	out.Y = config::screenH * .5f;

	out.X += 0.5f * _x * config::screenW + 0.5f;
	out.Y -= 0.5f * _y * config::screenH + 0.5f;

	if (out.X < 0 || out.Y < 0 || out.Y >= config::screenW || out.Y >= config::screenH) { return OW::Vector3(); }

	return out;
}
