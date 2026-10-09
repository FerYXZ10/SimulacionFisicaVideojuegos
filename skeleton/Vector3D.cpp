#include "Vector3D.h"
#include <cmath>

float Vector3D::magnitude() const noexcept {
	return std::sqrt(x * x + y * y + z * z);
}

Vector3D& Vector3D::normalize() noexcept {
	const float mag = magnitude();
	if (mag != 0) {
		x /= mag;
		y /= mag;
		z /= mag;
	}
	return *this;
}

float Vector3D::dot(const Vector3D& v) const noexcept{
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::cross(const Vector3D& v) const noexcept{
	return Vector3D(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}