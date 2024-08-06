#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstddef>

struct Vec3
{
    float X, Y, Z;
};

enum class HitboxType {
    Head = 0,
    Neck = 1,
    UpperChest = 2,
    LowerChest = 3,
    Stomach = 4,
    Hip = 5
};

struct MatrixArray {
    float matrix[16];
};

struct Matrix3x4 {
    float matrix[3][4];

    Vec3 GetPosition();
    Vec3 GetPosition2();
};

/*
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
*/
struct QAngle {

	float x;
	float y;

	QAngle() : x(0), y(0) {}

	QAngle(float x, float y) : x(x), y(y) {}

	inline QAngle operator+(const QAngle& other) const {
		return QAngle(x + other.x, y + other.y);
	}

	inline QAngle operator-(const QAngle& other) const {
		return QAngle(x - other.x, y - other.y);
	}

	inline QAngle operator*(const float scalar) const {
		return QAngle(x * scalar, y * scalar);
	}

	inline QAngle operator/(const float scalar) const {
		return QAngle(x / scalar, y / scalar);
	}

	inline QAngle& operator+=(const QAngle& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	inline QAngle& operator-=(const QAngle& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline QAngle& operator*=(const float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	inline QAngle& operator/=(const float scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	inline bool operator==(const QAngle& other) const
	{
		return x == other.x && y == other.y;
	}

	inline bool operator!=(const QAngle& other) const
	{
		return !(*this == other);
	}

	inline float dot(const QAngle& other) const {
		return x * other.x + y * other.y;
	}

	inline float length() const {
		return std::sqrt(x * x + y * y);
	}

	float distanceTo(const QAngle& other) const {
		return (other - *this).length();
	};

	inline QAngle& normalize() {
		float len = length();
		if (len > 0) {
			x /= len;
			y /= len;
		}
		return *this;
	}

	inline QAngle& clamp(float minVal, float maxVal) {
		x = std::clamp(x, minVal, maxVal);
		y = std::clamp(y, minVal, maxVal);

		return *this;
	}

	inline QAngle lerp(const QAngle& other, float t) const {
		return (*this) * (1.0f - t) + other * t;
	}

	inline QAngle& fixAngle() {
		if (!isValid()) {
			return *this;
		}

		while (y > 89.0f)
			y -= 180.f;

		while (y < -89.0f)
			y += 180.f;

		while (x > 180.f)
			x -= 360.f;

		while (x < -180.f)
			x += 360.f;

		return *this;
	}

	inline bool isValid() const {
		if (std::isnan(x) || std::isinf(x) || std::isnan(y) || std::isinf(y)) {
			return false;
		}

		return true;
	}

	inline static QAngle zero() {
		return QAngle(0, 0);
	}
};

