#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Ray.h"

class Primitive {
public:
	virtual float intersectionPoint(Ray ray) = 0;
	virtual Colour calculateShading(Vector3 lightPos, Colour lightColour, Ray ray, float t) = 0;

	Primitive();
};

#endif
