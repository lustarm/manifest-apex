#include "headers/target.h"
#include <complex>   // For std::complex
#include <algorithm> // For std::min
#include <cfloat>    // For FLT_MAX

QAngle CalculateAngle(Vec3 from, OW::Vector3 to) 
{
	Vec3 newDirection = { GameUnitsToMeter(to.X - from.X),GameUnitsToMeter(to.Y - from.Y),GameUnitsToMeter(to.Z - from.Z) };
	float lens = sqrtf(newDirection.X * newDirection.X + newDirection.Y * newDirection.Y + newDirection.Z * newDirection.Z);
	/*if (lens > 0) {
		newDirection.x /= lens;
		newDirection.y /= lens;
		newDirection.z /= lens;
	}*/
	float pitch = atan2f(newDirection.Z * (-1.f), lens) * (180.f / M_PI);//-asinf(newDirection.z) * (180 / M_PI);
	float yaw = atan2f(newDirection.Y, newDirection.X) * (180.f / M_PI);
	QAngle returnangle{ pitch, yaw };
	return returnangle;
}
QAngle SmoothLinear(QAngle LocalAngle, QAngle TargetAngle, float speed)
{
	QAngle Result = LocalAngle;

	float deltax, deltay;
	deltax = (TargetAngle.x - LocalAngle.x) * speed;
	deltay = (TargetAngle.y - LocalAngle.y) * speed;

	Result.x = LocalAngle.x + deltax;
	Result.y = LocalAngle.y + deltay;

	return Result;
}

/*
OW::Vector3 W2S(MatrixArray matrix, OW::Vector3 Position) {
    OW::Vector3 out;
    float _x = matrix.matrix[0] * Position.X + matrix.matrix[1] * Position.Y + matrix.matrix[2] * Position.Z + matrix.matrix[3];
    float _y = matrix.matrix[4] * Position.X + matrix.matrix[5] * Position.Y + matrix.matrix[6] * Position.Z + matrix.matrix[7];
    out.Z = matrix.matrix[12] * Position.X + matrix.matrix[13] * Position.Y + matrix.matrix[14] * Position.Z + matrix.matrix[15];
 
    if (out.Z < 0.1f) return {0,0,0};
 
    _x *= 1.f / out.Z;
    _y *= 1.f / out.Z;
 
	out.X = config::screenH * .5f;
    out.Y = config::screenW * .5f;
 
    out.X += 0.5f * _x * config::screenH + 0.5f;
    out.Y -= 0.5f * _y * config::screenW + 0.5f;

    return out;
}
*/

struct OW::Vector3 _WorldToScreen(const struct OW::Vector3 pos, struct MatrixArray matrix) {
	struct OW::Vector3 out;
	float _x = matrix.matrix[0] * pos.X + matrix.matrix[1] * pos.Y + matrix.matrix[2] * pos.Z + matrix.matrix[3];
	float _y = matrix.matrix[4] * pos.X + matrix.matrix[5] * pos.Y + matrix.matrix[6] * pos.Z + matrix.matrix[7];
	out.Z = matrix.matrix[12] * pos.X + matrix.matrix[13] * pos.Y + matrix.matrix[14] * pos.Z + matrix.matrix[15];
	if (out.Z > 0.001f) {
		_x *= 1.f / out.Z;
		_y *= 1.f / out.Z;

		int width = config::screenW;
		int height = config::screenH;

		out.X = width * .5f;
		out.Y = height * .5f;

		out.X += 0.5f * _x * width + 0.5f;
		out.Y -= 0.5f * _y * height + 0.5f;

		return out;
	}
	else return OW::Vector3(9999, 9999, 0);
}


void SolveQuartic(const std::complex<float> coefficients[5], std::complex<float> roots[4]) {
	const std::complex<float> a = coefficients[4];
	const std::complex<float> b = coefficients[3] / a;
	const std::complex<float> c = coefficients[2] / a;
	const std::complex<float> d = coefficients[1] / a;
	const std::complex<float> e = coefficients[0] / a;

	const std::complex<float> Q1 = c * c - 3.f * b * d + 12.f * e;
	const std::complex<float> Q2 = 2.f * c * c * c - 9.f * b * c * d + 27.f * d * d + 27.f * b * b * e - 72.f * c * e;
	const std::complex<float> Q3 = 8.f * b * c - 16.f * d - 2.f * b * b * b;
	const std::complex<float> Q4 = 3.f * b * b - 8.f * c;

	const std::complex<float> Q5 = std::pow(Q2 / 2.f + std::sqrt(Q2 * Q2 / 4.f - Q1 * Q1 * Q1), 1.f / 3.f);
	const std::complex<float> Q6 = (Q1 / Q5 + Q5) / 3.f;
	const std::complex<float> Q7 = 2.f * std::sqrt(Q4 / 12.f + Q6);

	roots[0] = (-b - Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
	roots[1] = (-b - Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
	roots[2] = (-b + Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
	roots[3] = (-b + Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
}


void AimCorrection(OW::Vector3 LocalPos, float scale1, OW::Vector3* InVecArg, OW::Vector3 currVelocity, float Bulletspeed)
{
    // Convert game units to meters for accurate calculations
    auto GameUnitsToMeter = [](float value) { return value * 0.01f; }; // Example conversion factor
    auto MeterToGameUnits = [](float value) { return value * 100.0f; }; // Example conversion factor

    // Convert to meters
    double G = GameUnitsToMeter(750.0f / scale1);
    double A = GameUnitsToMeter(LocalPos.Y);
    double B = GameUnitsToMeter(LocalPos.Z);
    double C = GameUnitsToMeter(LocalPos.X);
    double M = GameUnitsToMeter(InVecArg->Y);
    double N = GameUnitsToMeter(InVecArg->Z);
    double O = GameUnitsToMeter(InVecArg->X);
    double P = GameUnitsToMeter(currVelocity.Y);
    double Q = GameUnitsToMeter(currVelocity.Z);
    double R = GameUnitsToMeter(currVelocity.X);
    double S = GameUnitsToMeter(Bulletspeed);

    // Calculate coefficients of the quartic polynomial
    double H = M - A;
    double J = O - C;
    double K = N - B;
    double L = -0.5 * G;
    double c4 = L * L;
    double c3 = -2 * Q * L;
    double c2 = (Q * Q) - (2 * K * L) - (S * S) + (P * P) + (R * R);
    double c1 = (2 * K * Q) + (2 * H * P) + (2 * J * R);
    double c0 = (K * K) + (H * H) + (J * J);

    // Solve the quartic polynomial
    std::complex<float> pOutRoots[4];
    const std::complex<float> pInCoeffs[5] = { static_cast<float>(c0), static_cast<float>(c1), static_cast<float>(c2), static_cast<float>(c3), static_cast<float>(c4) };
    SolveQuartic(pInCoeffs, pOutRoots);

    // Find the smallest positive real root
    float fBestRoot = FLT_MAX;
    for (const auto& root : pOutRoots) {
        if (root.real() > 0.f && std::abs(root.imag()) < 0.0001f) {
            fBestRoot = (std::min)(fBestRoot, root.real());
        }
    }

    // Check if we found a valid root
    if (fBestRoot == FLT_MAX) {
        // No valid root found; handle this case as needed
        return;
    }

    // Update the target vector with the calculated correction
    InVecArg->Y = MeterToGameUnits(A + (H + P * fBestRoot));
    InVecArg->Z = MeterToGameUnits(B + (K + Q * fBestRoot - L * fBestRoot * fBestRoot));
    InVecArg->X = MeterToGameUnits(C + (J + R * fBestRoot));
}