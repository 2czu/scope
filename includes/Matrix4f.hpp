/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix4f.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:14:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/19 12:07:56 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cmath>
#include <array>
#include <iostream>

#include "Vector3f.hpp"

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
        r.m[12] = t.x; // colonne 4, ligne 1
        r.m[13] = t.y; // colonne 4, ligne 2
        r.m[14] = t.z; // colonne 4, ligne 3
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

    // multiplication colonne-major
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

};
