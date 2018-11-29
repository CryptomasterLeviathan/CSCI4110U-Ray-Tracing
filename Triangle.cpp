#include <cmath>
#include <iostream>

#include "Triangle.h"
#include "Util.h"


float Triangle::intersectionPoint(Ray ray) {
	//float denominator = ray.direction.dot(this->surfaceNormal);
	Vector3 v01 = v1 - v0;
	Vector3 v02 = v2 - v0;
	Vector3 pv = ray.direction.cross(v02);
	float det = v01.dot(pv);
	//std::cout << det << std::endl;
	if (det < 0.000001f)
		return -1;


	float invDet = 1 / det;
	Vector3 tv = ray.origin - v0;
	float u = tv.dot(pv) * invDet;
	if (u < 0 || u > 1)
		return -1;


	Vector3 qv = tv.cross(v01);
	float v = ray.origin.dot(qv) * invDet;
	std::cout << v << std::endl;
	if (v < 0 || u + v > 1)
		return -1;

	float t = v02.dot(qv) * invDet;
	std::cout << t << std::endl;
	return t;
}

Colour Triangle::calculateShading(Vector3 lightPos, Colour lightColour, Ray ray, float t) {
	//return COLOUR_CYAN;

	// calculate the point on the plane's surface
	Vector3 pointOnSurface = ray.origin + (ray.direction * t);

	// calculate the light path vector
	Vector3 lightPathVector = lightPos - pointOnSurface;

	// calculate the surface normal for the plane
	Vector3 surfaceNormal = this->surfaceNormal;
	surfaceNormal.normalize();

	// calculate the eye path vector
	Vector3 eyePathVector = ray.origin - pointOnSurface;
	eyePathVector.normalize();

	// calculate the diffuse contribution using the Lambertian model
	float diffuseCoefficient = clamp(surfaceNormal.dot(lightPathVector));
	Colour diffuseColour = this->material.colour * diffuseCoefficient;

	// calculate the light reflection vector
	Vector3 lightReflectionVector = lightPathVector + surfaceNormal * -2.0f * surfaceNormal.dot(lightPathVector);
	lightReflectionVector.normalize();
	Vector3 r = lightPathVector - (surfaceNormal * (2.0f * surfaceNormal.dot(lightPathVector)));

	// calculate the specular contribution using the Blinn-Phong model
	Vector3 h = lightPathVector + eyePathVector;
	h.normalize();
	float z = max(0.0f, h.dot(surfaceNormal));
	float specFactor = (8.0f + this->material.shininess) / (8.0f * PI);
	Colour specularColour = lightColour * this->material.specularCoefficient * specFactor * pow(z, this->material.shininess);

	// calculate the ambient colour
	Colour ambientColour = this->material.colour * ambientCoefficient;

	// combine specular, diffuse, and ambient lighting contributions
	return ambientColour + diffuseColour + specularColour;
}
