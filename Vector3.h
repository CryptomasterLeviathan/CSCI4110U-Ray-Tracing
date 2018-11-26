#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {

public:
	float x, y, z;

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

	Vector3 operator+(const Vector3& rhs);
	Vector3 operator-(const Vector3& rhs);
	Vector3 operator*(const float rhs);
	void normalize();

	float dot(Vector3 other);
};

#endif
