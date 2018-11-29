#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Primitive.h"
#include "Material.h"

class Triangle : public Primitive {
public:
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;
	Vector3 surfaceNormal;
	Material material;
	float ambientCoefficient = 0.1f;

	Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 surfaceNormal, Material material) : v0(v0), v1(v1), v2(v2), surfaceNormal(surfaceNormal), material(material) {}

	virtual float intersectionPoint(Ray ray);
	virtual Colour calculateShading(Vector3 lightPos, Colour lightColour, Ray ray, float t);
};

#endif
