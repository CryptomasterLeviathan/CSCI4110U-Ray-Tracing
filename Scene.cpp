#include "Scene.h"

Scene::Scene() : eyeLocation(Vector3 (0.5f, 0.5f, -10.0f)), lightPosition(Vector3(0.5f, 10.0f, -2.0f)), lightColour(Colour(1.0f, 1.0f, 1.0f, 1.0f)) {
	Material yellowMaterial(COLOUR_YELLOW, 0.5f, 0.5f, 80.0f);
	Vector3 sphere1Centre(0.5f, 0.2f, 0.25f);
	Sphere* sphere1 = new Sphere(sphere1Centre, 0.2, yellowMaterial);

	Material redMaterial(COLOUR_RED, 0.2f, 0.8f, 200.0f);
	Vector3 sphere2Centre(0.2f, 0.15f, 0.6f);
	Sphere* sphere2 = new Sphere(sphere2Centre, 0.15f, redMaterial);

	Material blueMaterial(COLOUR_BLUE, 0.8f, 0.2f, 5.0f);
	Vector3 sphere3Centre(0.8f, 0.1f, 0.75f);
	Sphere* sphere3 = new Sphere(sphere3Centre, 0.1f, blueMaterial);

	Material lightGrayMaterial(COLOUR_LIGHT_GRAY, 0.5f, 0.5f, 100.0f);
	Vector3 planeOrigin(0.0f, 0.0f, 0.0f);
	Vector3 planeNormal(0.0f, 1.0f, 0.0f); 
	Plane* ground = new Plane(planeOrigin, planeNormal, lightGrayMaterial);

	Vector3 v0(0.2f, 0.2f, 0.2f);
	Vector3 v1(0.8f, 0.2f, 0.2f);
	Vector3 v2(0.5f, 0.8f, 0.2f);
	Vector3 triNormal(0.0f, 0.0f, 1.0f);
	Triangle* triangle = new Triangle(v2, v1, v0, triNormal, redMaterial);

	//objects.push_back(sphere1);
	//objects.push_back(sphere2);
	objects.push_back(sphere3);
	//objects.push_back(ground);
	objects.push_back(triangle);
}

Colour Scene::Trace(Vector3 pixelLocation) {
	Vector3 direction = pixelLocation - eyeLocation;
	direction.normalize();
	Ray ray(eyeLocation, direction);

	std::vector<Primitive*>::iterator ptr;
	for (ptr = objects.begin(); ptr < objects.end(); ptr++) {
		Primitive* obj = *ptr;
		float t = obj->intersectionPoint(ray);

		if (!std::isnan(t) && t > 0.0f) {
			// TODO: Check for minT before calculating colour
			return obj->calculateShading(lightPosition, lightColour, ray, t);
		}
	}

	return COLOUR_BLACK;
}
