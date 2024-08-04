#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstddef>

enum class HitboxType {
    Head = 0,
    Neck = 1,
    UpperChest = 2,
    LowerChest = 3,
    Stomach = 4,
    Hip = 5
};

struct Color {
    float red;
    float green;
    float blue;

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
};

struct GlowMode {
    std::byte bodyStyle, borderStyle, borderWidth, transparency;

    GlowMode();
    GlowMode(int bodyStyle_val, int borderStyle_val, int borderWidth_val, int transparency_val);
    GlowMode(std::byte bodyStyle_val, std::byte borderStyle_val, std::byte borderWidth_val, std::byte transparency_val);

    bool isZeroVector() const;
    void print() const;
    bool operator==(const GlowMode& other) const;
    bool operator!=(const GlowMode& other) const;
};

struct Vector3 {
    float x, y, z;
};

struct Matrix {
    float matrix[16];
};

struct Vec3 {
    float x, y, z;

    Vec3();
    Vec3(float _x, float _y, float _z);

    bool operator==(const float _t);
    bool operator==(Vec3 _t);
    bool operator!=(Vec3 _t);
    bool operator<(const float _t);
    bool operator>(const float _t);
    bool operator>=(const float _t);
    bool operator<=(const float _t);
    bool operator!=(const float _t);
};

struct Vec2 {
    float x, y;

    Vec2();
    Vec2(float _x, float _y);
    Vec2(Vec3 _t);

    bool operator==(const float _t);
    bool operator<(const float _t);
    bool operator>(const float _t);
    bool operator>=(const float _t);
    bool operator<=(const float _t);
    bool operator!=(const float _t);
};

struct QAngle {
    float x;
    float y;

    QAngle();
    QAngle(float x, float y);

    QAngle operator+(const QAngle& other) const;
    QAngle operator-(const QAngle& other) const;
    QAngle operator*(const float scalar) const;
    QAngle operator/(const float scalar) const;
    QAngle& operator+=(const QAngle& other);
    QAngle& operator-=(const QAngle& other);
    QAngle& operator*=(const float scalar);
    QAngle& operator/=(const float scalar);
    bool operator==(const QAngle& other) const;
    bool operator!=(const QAngle& other) const;

    float dot(const QAngle& other) const;
    float length() const;
    float distanceTo(const QAngle& other) const;
    QAngle& normalize();
    QAngle& clamp(float minVal, float maxVal);
    QAngle lerp(const QAngle& other, float t) const;
    QAngle& fixAngle();
    bool isValid() const;

    static QAngle zero();
};

struct Matrix3x4 {
public:
    float matrix[3][4];

    Vec3 GetPosition() const;
    Vec3 GetPosition2() const;
};
