#include <cmath>
#include <windows.h>

#include "headers/structs.h"
#include "headers/render.hpp"

using namespace OW;

// Rect
Rect::Rect() : x(0), y(0), width(0), height(0) {}

Rect::Rect(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

bool Rect::operator==(const Rect& src) const {
    return (src.x == x && src.y == y && src.height == height && src.width == width);
}

bool Rect::operator!=(const Rect& src) const {
    return (src.x != x || src.y != y || src.height != height || src.width != width);
}

// Vector2
Vector2::Vector2() : X(0), Y(0) {}

Vector2::Vector2(float _X, float _Y) : X(_X), Y(_Y) {}

float Vector2::Distance(Vector2 v) const {
    return std::sqrt(std::pow(v.X - X, 2.0f) + std::pow(v.Y - Y, 2.0f));
}

float Vector2::get_length() const {
    return std::sqrt(std::pow(X, 2.0f) + std::pow(Y, 2.0f));
}

Vector2 Vector2::operator+(Vector2 v) const {
    return { X + v.X, Y + v.Y };
}

Vector2 Vector2::operator-(Vector2 v) const {
    return { X - v.X, Y - v.Y };
}

// Vector3
Vector3::Vector3() : X(0), Y(0), Z(0) {}

Vector3::Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

Vector3 Vector3::operator-(const Vector3& V) const {
    return Vector3(X - V.X, Y - V.Y, Z - V.Z);
}

Vector3 Vector3::operator+(const Vector3& V) const {
    return Vector3(X + V.X, Y + V.Y, Z + V.Z);
}

Vector3 Vector3::operator*(float Scale) const {
    return Vector3(X * Scale, Y * Scale, Z * Scale);
}

Vector3 Vector3::operator/(float Scale) const {
    float RScale = 1.f / Scale;
    return Vector3(X * RScale, Y * RScale, Z * RScale);
}

Vector3 Vector3::operator+(float A) const {
    return Vector3(X + A, Y + A, Z + A);
}

Vector3 Vector3::operator-(float A) const {
    return Vector3(X - A, Y - A, Z - A);
}

Vector3 Vector3::operator*(const Vector3& V) const {
    return Vector3(X * V.X, Y * V.Y, Z * V.Z);
}

Vector3 Vector3::operator/(const Vector3& V) const {
    return Vector3(X / V.X, Y / V.Y, Z / V.Z);
}

float Vector3::operator|(const Vector3& V) const {
    return X * V.X + Y * V.Y + Z * V.Z;
}

float Vector3::operator^(const Vector3& V) const {
    return X * V.Y - Y * V.X - Z * V.Z;
}

Vector3& Vector3::operator+=(const Vector3& v) {
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& v) {
    X *= v.X;
    Y *= v.Y;
    Z *= v.Z;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& v) {
    X /= v.X;
    Y /= v.Y;
    Z /= v.Z;
    return *this;
}

bool Vector3::operator==(const Vector3& src) const {
    return (src.X == X) && (src.Y == Y) && (src.Z == Z);
}

bool Vector3::operator!=(const Vector3& src) const {
    return (src.X != X) || (src.Y != Y) || (src.Z != Z);
}

Vector3 Vector3::Rotate(float angle) const {
    return Vector3(X * std::cos(-angle) - Z * std::sin(-angle), Y, X * std::sin(-angle) + Z * std::cos(-angle));
}

float Vector3::Size() const {
    return std::sqrt(X * X + Y * Y + Z * Z);
}

float Vector3::get_length() const {
    float ret = std::sqrt(std::pow(X, 2) + std::pow(Y, 2) + std::pow(Z, 2));
    return max(ret, 0.000000000000000000000000000000001f);
}

float Vector3::DistTo(Vector3 targetTo) const {
    return (targetTo - *this).Size();
}

Vector3 Vector3::toRotator(Vector3 targetTo) const {
    Vector3 Normalized = (targetTo - *this);
    return Normalized * (1 / Normalized.Size());
}

// Color
Color::Color(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}

Color::Color(float Input[3]) 
    : R(static_cast<uint8_t>(Input[0] * 255.f)),
      G(static_cast<uint8_t>(Input[1] * 255.f)),
      B(static_cast<uint8_t>(Input[2] * 255.f)) {}

Color::Color(XMFLOAT3 Input) 
    : R(static_cast<uint8_t>(Input.x * 255.f)),
      G(static_cast<uint8_t>(Input.y * 255.f)),
      B(static_cast<uint8_t>(Input.z * 255.f)) {}

DWORD Color::C2D() const {
    return ((A & 0xff) << 24) | ((B & 0xff) << 16) | ((G & 0xff) << 8) | (R & 0xff);
}

DWORD Color::ApplyAlpha(int Alpha) const {
    return ((Alpha & 0xff) << 24) | (R & 0xff) | ((G & 0xff) << 8) | ((B & 0xff) << 16);
}

DWORD Color::RGBA2ARGB(int Alpha) const {
    return ((Alpha & 0xff) << 24) | (B & 0xff) | ((G & 0xff) << 8) | ((R & 0xff) << 16);
}

// Matrix
XMFLOAT3 Matrix::get_location() const {
    XMMATRIX invView = XMMatrixInverse(NULL, (XMMATRIX)*this);
    return XMFLOAT3(XMVectorGetX(invView.r[3]) / XMVectorGetW(invView.r[3]),
                    XMVectorGetY(invView.r[3]) / XMVectorGetW(invView.r[3]),
                    XMVectorGetZ(invView.r[3]) / XMVectorGetW(invView.r[3]));
}

XMFLOAT3 Matrix::get_rotation() const {
    return XMFLOAT3(XMVectorGetZ(r[0]), XMVectorGetZ(r[1]), XMVectorGetZ(r[2]));
}

Vector3 Matrix::GetCameraVec() const {
    float A = m22 * m33 - m32 * m23;
    float B = m32 * m13 - m12 * m33;
    float C = m12 * m23 - m22 * m13;
    float Z = m11 * A + m21 * B + m31 * C;

    if (std::abs(Z) < 0.0001f) return Vector3();

    float D = m31 * m23 - m21 * m33;
    float E = m11 * m33 - m31 * m13;
    float F = m21 * m13 - m11 * m23;
    float G = m21 * m32 - m31 * m22;
    float H = m31 * m12 - m11 * m32;
    float K = m11 * m22 - m21 * m12;

    return Vector3(-(A * m41 + D * m42 + G * m43) / Z,
                   -(B * m41 + E * m42 + H * m43) / Z,
                   -(C * m41 + F * m42 + K * m43) / Z);
}

bool Matrix::WorldToScreen(Vector3 worldPos, Vector2* OutPos, Vector2 WindowSize, bool ignoreret) const {
    float screenX = (r[0].m128_f32[0] * worldPos.X) + (r[1].m128_f32[0] * worldPos.Y) + (r[2].m128_f32[0] * worldPos.Z) + r[3].m128_f32[0];
    float screenY = (r[0].m128_f32[1] * worldPos.X) + (r[1].m128_f32[1] * worldPos.Y) + (r[2].m128_f32[1] * worldPos.Z) + r[3].m128_f32[1];
    float screenW = (r[0].m128_f32[3] * worldPos.X) + (r[1].m128_f32[3] * worldPos.Y) + (r[2].m128_f32[3] * worldPos.Z) + r[3].m128_f32[3];

    float camX = WindowSize.X / 2.0f;
    float camY = WindowSize.Y / 2.0f;
    float x = camX + (camX * screenX / screenW);
    float y = camY - (camY * screenY / screenW);

    if (x < 0 || y < 0 || x >= WindowSize.X || y >= WindowSize.Y) { return false; }

    *OutPos = { x, y };

    return (screenW > 0.001f) || ignoreret;
}

Vector2 Matrix::WorldToScreenVec2(Vector3 worldPos) const {
    float screenX = (r[0].m128_f32[0] * worldPos.X) + (r[1].m128_f32[0] * worldPos.Y) + (r[2].m128_f32[0] * worldPos.Z) + r[3].m128_f32[0];
    float screenY = (r[0].m128_f32[1] * worldPos.X) + (r[1].m128_f32[1] * worldPos.Y) + (r[2].m128_f32[1] * worldPos.Z) + r[3].m128_f32[1];
    float screenW = (r[0].m128_f32[3] * worldPos.X) + (r[1].m128_f32[3] * worldPos.Y) + (r[2].m128_f32[3] * worldPos.Z) + r[3].m128_f32[3];

    if (screenW <= 0.1f)
        screenW = 0.1f;

    float camX = GetSystemMetrics(SM_CXSCREEN) / 2.0f;
    float camY = GetSystemMetrics(SM_CYSCREEN) / 2.0f;

    float x = camX + (camX * screenX / screenW) + screenX / screenW;
    float y = camY - (camY * screenY / screenW) + screenY / screenW;

    if (x < 0 || y < 0 || x >= GetSystemMetrics(SM_CXSCREEN) || y >= GetSystemMetrics(SM_CYSCREEN)) { return Vector2{}; }

    return { x, y };
}
