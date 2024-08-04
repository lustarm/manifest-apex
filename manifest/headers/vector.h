#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")

#include "structs.h"

using namespace DirectX;

namespace OW {
    class Rect {
    public:
        float x;
        float y;
        float width;
        float height;

        Rect();
        Rect(float x, float y, float width, float height);

        bool operator==(const Rect& src) const;
        bool operator!=(const Rect& src) const;
    };

    class Vector2 {
    public:
        float X, Y;

        Vector2();
        Vector2(float _X, float _Y);

        float Distance(Vector2 v) const;
        float get_length() const;

        Vector2 operator+(Vector2 v) const;
        Vector2 operator-(Vector2 v) const;
    };

    struct Vector3 {
    public:
        float X;
        float Y;
        float Z;

        Vector3();
        Vector3(float x, float y, float z);

        Vector3 operator-(const Vector3& V) const;
        Vector3 operator+(const Vector3& V) const;
        Vector3 operator*(float Scale) const;
        Vector3 operator/(float Scale) const;
        Vector3 operator+(float A) const;
        Vector3 operator-(float A) const;
        Vector3 operator*(const Vector3& V) const;
        Vector3 operator/(const Vector3& V) const;
        float operator|(const Vector3& V) const;
        float operator^(const Vector3& V) const;

        Vector3& operator+=(const Vector3& v);
        Vector3& operator-=(const Vector3& v);
        Vector3& operator*=(const Vector3& v);
        Vector3& operator/=(const Vector3& v);

        bool operator==(const Vector3& src) const;
        bool operator!=(const Vector3& src) const;

        Vector3 Rotate(float angle) const;
        float Size() const;
        float get_length() const;
        float DistTo(Vector3 targetTo) const;
        Vector3 toRotator(Vector3 targetTo) const;
    };

    struct Color {
        uint8_t A{ 255 };
        uint8_t R{ 255 };
        uint8_t G{ 255 };
        uint8_t B{ 255 };

        Color(int r, int g, int b, int a = 255);
        Color(float Input[3]);
        Color(XMFLOAT3 Input);

        DWORD C2D() const;
        DWORD ApplyAlpha(int Alpha) const;
        DWORD RGBA2ARGB(int Alpha) const;
    };

    class Matrix : public XMMATRIX {
    public:
        float m11, m12, m13, m14,
              m21, m22, m23, m24,
              m31, m32, m33, m34,
              m41, m42, m43, m44;

        XMFLOAT3 get_location() const;
        XMFLOAT3 get_rotation() const;
        Vector3 GetCameraVec() const;

        bool WorldToScreen(Vector3 worldPos, Vector2* OutPos, Vector2 WindowSize, bool ignoreret = false) const;
        Vector2 WorldToScreenVec2(Vector3 worldPos) const;
    };
}

