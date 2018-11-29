#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cmath>

// TODO: Change this to Object.h when I create that class
#include "Primitive.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

#include "Ray.h"
#include "Vector3.h"
#include "Material.h"
#include "Colour.h"
#include "ColourDefinitions.h"

class Scene {
	Vector3 eyeLocation;
	std::vector<Primitive*> objects;

	// TODO: Support multiple lights
	Vector3 lightPosition;
	Colour lightColour;

	public:
	Scene();
	Colour Trace(Vector3 pixelLocation);
};

#endif
