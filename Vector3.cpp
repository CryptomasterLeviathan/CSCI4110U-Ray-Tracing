#include <cmath>

#include "Vector3.h"

float Vector3::dot(Vector3 other) {
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::cross(Vector3 other) {
	Vector3 result;

	result.x = this->y * other.z - this->z * other.y;
	result.y = this->z * other.x - this->x * other.z;
	result.z = this->x * other.y - this->y * other.x;

	return result;
}

Vector3 Vector3::operator+(const Vector3& rhs) {
	Vector3 result;

	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;
	result.z = this->z + rhs.z;

	return result;
}

Vector3 Vector3::operator-(const Vector3& rhs) {
	Vector3 result;

	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;
	result.z = this->z - rhs.z;

	return result;
}

Vector3 Vector3::operator*(const float rhs) {
	Vector3 result;

	result.x = this->x * rhs;
	result.y = this->y * rhs;
	result.z = this->z * rhs;

	return result;
}

void Vector3::normalize() {
	float length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	this->x = this->x / length;
	this->y = this->y / length;
	this->z = this->z / length;
}

