#include "headers/w2s.h"

bool W2S(MatrixArray matrix, OW::Vector3 pos, OW::Vector2* OutPos, OW::Vector2 WindowSize)
{
	struct OW::Vector3 out;
	float _x = matrix.matrix[0] * pos.X + matrix.matrix[1] * pos.Y + matrix.matrix[2] * pos.Z + matrix.matrix[3];
	float _y = matrix.matrix[4] * pos.X + matrix.matrix[5] * pos.Y + matrix.matrix[6] * pos.Z + matrix.matrix[7];
	out.Z = matrix.matrix[12] * pos.X + matrix.matrix[13] * pos.Y + matrix.matrix[14] * pos.Z + matrix.matrix[15];

	_x *= 1.f / out.Z;
	_y *= 1.f / out.Z;

	int width = config::screenW;
	int height = config::screenH;

	out.X = width * .5f;
	out.Y = height * .5f;

	out.X += 0.5f * _x * width + 0.5f;
	out.Y -= 0.5f * _y * height + 0.5f;

	if (out.X < 0 || out.Y < 0 || out.Y >= config::screenW || out.Y >= config::screenH) { return false; }
	OutPos->X = out.X;
	OutPos->Y = out.Y;
	return out.Z > 0.001f;
}
