#pragma once
#include <cmath>
#include <iostream>

class Vector3f {
public:
    float x, y, z;

    Vector3f() : x(0), y(0), z(0) {}
    Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3f(const Vector3f& v) = default;
    Vector3f& operator=(const Vector3f& v) = default;

    Vector3f operator+(const Vector3f& v) const { return Vector3f(x + v.x, y + v.y, z + v.z); }
    Vector3f operator-(const Vector3f& v) const { return Vector3f(x - v.x, y - v.y, z - v.z); }
    Vector3f operator*(float scalar) const { return Vector3f(x * scalar, y * scalar, z * scalar); }
    Vector3f operator/(float scalar) const { return Vector3f(x / scalar, y / scalar, z / scalar); }

    Vector3f& operator+=(const Vector3f& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3f& operator-=(const Vector3f& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3f& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    Vector3f& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    float length() const { return std::sqrt(x*x + y*y + z*z); }

    Vector3f normalized() const {
        float len = length();
        return (len == 0) ? Vector3f(0,0,0) : Vector3f(x/len, y/len, z/len);
    }

    float dot(const Vector3f& v) const { return x*v.x + y*v.y + z*v.z; }

    Vector3f cross(const Vector3f& v) const {
        return Vector3f(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    void print() const { std::cout << "(" << x << ", " << y << ", " << z << ")\n"; }
};

inline Vector3f operator*(float scalar, const Vector3f& v) {
    return v * scalar;
}
