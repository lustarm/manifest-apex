#include "headers/structs.h"

bool Color::operator==(const Color& other) const {
    return (red == other.red) && (green == other.green) && (blue == other.blue);
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}

/*
GlowMode::GlowMode() {}

GlowMode::GlowMode(int bodyStyle_val, int borderStyle_val, int borderWidth_val, int transparency_val) :
    bodyStyle(static_cast<std::byte>(bodyStyle_val)),
    borderStyle(static_cast<std::byte>(borderStyle_val)),
    borderWidth(static_cast<std::byte>(borderWidth_val)),
    transparency(static_cast<std::byte>(transparency_val)) {}

GlowMode::GlowMode(std::byte bodyStyle_val, std::byte borderStyle_val, std::byte borderWidth_val, std::byte transparency_val) :
    bodyStyle(bodyStyle_val),
    borderStyle(borderStyle_val),
    borderWidth(borderWidth_val),
    transparency(transparency_val) {}

bool GlowMode::isZeroVector() const {
    return bodyStyle == std::byte(0)
        && borderStyle == std::byte(0)
        && borderWidth == std::byte(0)
        && transparency == std::byte(0);
}

void GlowMode::print() const {
    std::cout
        << "bodyStyle:" << static_cast<int>(bodyStyle)
        << " borderStyle:" << static_cast<int>(borderStyle)
        << " borderWidth:" << static_cast<int>(borderWidth)
        << " transparency:" << static_cast<int>(transparency)
        << "\n";
}

bool GlowMode::operator==(const GlowMode& other) const {
    return bodyStyle == other.bodyStyle
        && borderStyle == other.borderStyle
        && borderWidth == other.borderWidth
        && transparency == other.transparency;
}

bool GlowMode::operator!=(const GlowMode& other) const {
    return !(*this == other);
}
*/

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

bool Vec3::operator==(const float _t) {
    return x == _t && y == _t && z == _t;
}

bool Vec3::operator==(Vec3 _t) {
    return x == _t.x && y == _t.y && z == _t.z;
}

bool Vec3::operator!=(Vec3 _t) {
    return x != _t.x || y != _t.y || z != _t.z;
}

bool Vec3::operator<(const float _t) {
    return x < _t && y < _t && z < _t;
}

bool Vec3::operator>(const float _t) {
    return x > _t && y > _t && z > _t;
}

bool Vec3::operator>=(const float _t) {
    return x >= _t && y >= _t && z >= _t;
}

bool Vec3::operator<=(const float _t) {
    return x <= _t && y <= _t && z <= _t;
}

bool Vec3::operator!=(const float _t) {
    return x != _t || y != _t || z != _t;
}

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}

Vec2::Vec2(Vec3 _t) : x(_t.x), y(_t.y) {}

bool Vec2::operator==(const float _t) {
    return x == _t && y == _t;
}

bool Vec2::operator<(const float _t) {
    return x < _t && y < _t;
}

bool Vec2::operator>(const float _t) {
    return x > _t && y > _t;
}

bool Vec2::operator>=(const float _t) {
    return x >= _t && y >= _t;
}

bool Vec2::operator<=(const float _t) {
    return x <= _t && y <= _t;
}

bool Vec2::operator!=(const float _t) {
    return x != _t || y != _t;
}

QAngle::QAngle() : x(0), y(0) {}

QAngle::QAngle(float x, float y) : x(x), y(y) {}

QAngle QAngle::operator+(const QAngle& other) const {
    return QAngle(x + other.x, y + other.y);
}

QAngle QAngle::operator-(const QAngle& other) const {
    return QAngle(x - other.x, y - other.y);
}

QAngle QAngle::operator*(const float scalar) const {
    return QAngle(x * scalar, y * scalar);
}

QAngle QAngle::operator/(const float scalar) const {
    return QAngle(x / scalar, y / scalar);
}

QAngle& QAngle::operator+=(const QAngle& other) {
    x += other.x;
    y += other.y;
    return *this;
}

QAngle& QAngle::operator-=(const QAngle& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

QAngle& QAngle::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

QAngle& QAngle::operator/=(const float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

bool QAngle::operator==(const QAngle& other) const {
    return x == other.x && y == other.y;
}

bool QAngle::operator!=(const QAngle& other) const {
    return !(*this == other);
}

float QAngle::dot(const QAngle& other) const {
    return x * other.x +
