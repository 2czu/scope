/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:57:14 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/01 15:46:26 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cmath>
#include <array>
#include <iostream>

template <typename T>
T clamp(T value, T minVal, T maxVal)
{
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

inline double degToRad(float degrees) {
    return degrees * M_PI / 180.0;
}

struct Vector2f {
public:
    float x, y;

    Vector2f() : x(0), y(0) {}
    Vector2f(float x, float y) : x(x), y(y) {}
    Vector2f(const Vector2f& v) = default;
    Vector2f& operator=(const Vector2f& v) = default;

    Vector2f operator+(const Vector2f& v) const { return Vector2f(x + v.x, y + v.y); }
    Vector2f operator-(const Vector2f& v) const { return Vector2f(x - v.x, y - v.y); }
    Vector2f operator*(float scalar) const { return Vector2f(x * scalar, y * scalar); }
    Vector2f operator/(float scalar) const { return Vector2f(x / scalar, y / scalar); }

    Vector2f& operator+=(const Vector2f& v) { x += v.x; y += v.y; return *this; }
    Vector2f& operator-=(const Vector2f& v) { x -= v.x; y -= v.y; return *this; }
    Vector2f& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2f& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    float length() const { return std::sqrt(x*x + y*y); }

    Vector2f normalized() const {
        float len = length();
        return (len == 0) ? Vector2f(0, 0) : Vector2f(x / len, y / len);
    }

    float dot(const Vector2f& v) const { return x * v.x + y * v.y; }

    void print() const { std::cout << "(" << x << ", " << y << ")\n"; }
};

inline Vector2f operator*(float scalar, const Vector2f& v) {
    return v * scalar;
}


struct Vector3f {
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

    const float* data() const { return &x; }
float* data() { return &x; }

    void print() const { std::cout << "(" << x << ", " << y << ", " << z << ")\n"; }
};

inline Vector3f operator*(float scalar, const Vector3f& v) {
    return v * scalar;
}

inline std::ostream &operator<<(std::ostream &out, const Vector3f &v)
{
    out << "[" << v.x << "; " << v.y << "; " << v.z << "]";
    return (out);
}

struct Vertex {
    Vector3f position;
    Vector3f norm;
    Vector3f color;
    Vector2f uv;
};


struct Matrix4f {

    std::array<float,16> m; // column-major

    Matrix4f() {
        setIdentity();
    }

    explicit Matrix4f(float v) {
        m.fill(v);
    }

    static Matrix4f identity() {
        Matrix4f r(0.0f);
        r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;
        return r;
    }

    static Matrix4f zero() {
        return Matrix4f(0.0f);
    }

    static Matrix4f translation(const Vector3f& t) {
        Matrix4f r = identity();
        r.m[12] = t.x;
        r.m[13] = t.y;
        r.m[14] = t.z;
        return r;
    }

    static Matrix4f scaling(const Vector3f& s) {
        Matrix4f r = identity();
        r.m[0] = s.x;
        r.m[5] = s.y;
        r.m[10] = s.z;
        return r;
    }

    static Matrix4f rotationX(float a) {
        Matrix4f r = identity();
        float c = std::cos(a), s = std::sin(a);
        r.m[5] = c;  r.m[6]  = s;
        r.m[9] = -s; r.m[10] = c;
        return r;
    }

    static Matrix4f rotationY(float a) {
        Matrix4f r = identity();
        float c = std::cos(a), s = std::sin(a);
        r.m[0] = c;  r.m[2] = -s;
        r.m[8] = s;  r.m[10] = c;
        return r;
    }

    static Matrix4f rotationZ(float a) {
        Matrix4f r = identity();
        float c = std::cos(a), s = std::sin(a);
        r.m[0] = c;  r.m[1] = s;
        r.m[4] = -s; r.m[5] = c;
        return r;
    }

    Matrix4f operator*(const Matrix4f& o) const {
        Matrix4f r(0.0f);
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                for (int k = 0; k < 4; k++) {
                    r.m[col*4 + row] += m[k*4 + row] * o.m[col*4 + k];
                }
            }
        }
        return r;
    }

    Vector3f operator*(const Vector3f& v) const {
        Vector3f r;
        r.x = m[0]*v.x + m[4]*v.y + m[8]*v.z + m[12];
        r.y = m[1]*v.x + m[5]*v.y + m[9]*v.z + m[13];
        r.z = m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14];
        return r;
    }

    void setIdentity() {
        *this = identity();
    }

    void print() const {
        for (int row = 0; row < 4; row++) {
            std::cout << "[ ";
            for (int col = 0; col < 4; col++) {
                std::cout << m[col*4 + row];
                if (col < 3) std::cout << ", ";
            }
            std::cout << " ]\n";
        }
    }

	static Matrix4f rotationAxis(const Vector3f& axis, float angle)
	{
		Matrix4f r = identity();
		float c = std::cos(angle);
		float s = std::sin(angle);
		float t = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		r.m[0]  = t*x*x + c;
		r.m[1]  = t*x*y + z*s;
		r.m[2]  = t*x*z - y*s;
		r.m[3]  = 0.0f;

		r.m[4]  = t*x*y - z*s;
		r.m[5]  = t*y*y + c;
		r.m[6]  = t*y*z + x*s;
		r.m[7]  = 0.0f;

		r.m[8]  = t*x*z + y*s;
		r.m[9]  = t*y*z - x*s;
		r.m[10] = t*z*z + c;
		r.m[11] = 0.0f;

		r.m[12] = 0.0f;
		r.m[13] = 0.0f;
		r.m[14] = 0.0f;
		r.m[15] = 1.0f;

		return r;
	}

	static Matrix4f perspective(float fovRadians, float aspect, float near, float far)
	{
		Matrix4f r = zero();
		float f = 1.0f / std::tan(fovRadians / 2.0f);

		r.m[0]  = f / aspect;
		r.m[5]  = f;
		r.m[10] = (far + near) / (near - far);
		r.m[11] = -1.0f;
		r.m[14] = (2.0f * far * near) / (near - far);
		r.m[15] = 0.0f;

		return r;
    }

    static Matrix4f lookAt(const Vector3f& eye,
                       const Vector3f& target,
                       const Vector3f& up)
    {
        Vector3f f = (target - eye).normalized();
        Vector3f s = f.cross(up).normalized();
        Vector3f u = s.cross(f);

        Matrix4f r = Matrix4f::identity();

        // rotation part (column-major)
        r.m[0] = s.x;
        r.m[1] = u.x;
        r.m[2] = -f.x;

        r.m[4] = s.y;
        r.m[5] = u.y;
        r.m[6] = -f.y;

        r.m[8] = s.z;
        r.m[9] = u.z;
        r.m[10] = -f.z;

        r.m[12] = -s.dot(eye);
        r.m[13] = -u.dot(eye);
        r.m[14] =  f.dot(eye);

        return r;
    }


};
