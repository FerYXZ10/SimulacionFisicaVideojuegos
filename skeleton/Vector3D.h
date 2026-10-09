#pragma once

#include <PxPhysicsAPI.h>
#include <stdexcept>

class Vector3D
{
public:
	float x, y, z;

	Vector3D(float x = 0, float y = 0, float z = 0) noexcept : x(x), y(y), z(z) {}
	Vector3D(const physx::PxVec3& v) noexcept : x(v.x), y(v.y), z(v.z) {}

	float magnitude() const noexcept;
	Vector3D& normalize() noexcept;

	float dot(const Vector3D& v) const noexcept;
	Vector3D cross(const Vector3D& v) const noexcept;

	Vector3D operator =(const physx::PxVec3& v) noexcept {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector3D operator +(const Vector3D& v) const noexcept{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D operator -(const Vector3D& v) const noexcept{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	Vector3D operator *(float f) const noexcept{
		return Vector3D(x * f, y * f, z * f);
	}

	friend Vector3D operator *(float f, const Vector3D& v) noexcept {
		return Vector3D(v.x * f, v.y * f, v.z * f);
	}

	Vector3D operator /(float f) const {
		if (f == 0) throw std::runtime_error("Division by zero in Vector3D operator /");

		return Vector3D(x / f, y / f, z / f);
	}

	Vector3D operator /(const Vector3D& v) const {
		if (v.x == 0 || v.y == 0 || v.z == 0) throw std::runtime_error("Division by zero in Vector3D operator /");

		return Vector3D(x / v.x, y / v.y, z / v.z);
	}

	Vector3D operator +=(const Vector3D& v) noexcept {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3D operator -=(const Vector3D& v) noexcept {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3D operator *=(float f) noexcept {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Vector3D operator /=(float f) {
		if (f == 0) throw std::runtime_error("Division by zero in Vector3D operator /=");

		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	operator physx::PxVec3() const {
		return physx::PxVec3(x, y, z);
	}
};

