#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <GL/glut.h>
#include <GL/gl.h>

#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Vector3.h"
#include "Colour.h"
#include "ColourDefinitions.h"

int resolutionX = 500;
int resolutionY = 500;

Colour* raster;

Scene* scene;

#include <chrono>

std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();
//float originalLightZ = lightPosition.z;
//float originalLightX = lightPosition.x;

void update(void) {
	std::chrono::high_resolution_clock::time_point frameTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedTime = frameTime - lastFrameTime;
	float deltaT = elapsedTime.count();

	//lightPosition.z = originalLightZ + sinf(deltaT);
	//lightPosition.x = originalLightX + sinf(deltaT);

	// clear the raster
	for (int y = 0; y < resolutionY; y++) {
		for (int x = 0; x < resolutionX; x++) {
			raster[y * resolutionX + x] = COLOUR_BLACK;
		}
	}

	float stepSizeX = 1.0f / (float)resolutionX;
	float stepSizeY = 1.0f / (float)resolutionY;

	// trace the rays
	for (int y = 0; y < resolutionY; y++) {
		for (int x = 0; x < resolutionX; x++) {
			// create a ray from the eyeLocation to this point
			Vector3 pixelLocation;
			pixelLocation.x = ((float)x + 0.5f) * stepSizeX;
			pixelLocation.y = ((float)y + 0.5f) * stepSizeY;
			pixelLocation.z = -5.0f;

			raster[y * resolutionX + x] = scene->Trace(pixelLocation);
		}
	}

	glutPostRedisplay();
}

void display(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	unsigned int numPixels = resolutionX * resolutionY;

	// TODO: Holy memory leak, Batman!!!
	float* pixelData = new float[numPixels * 3];

	for (unsigned int i = 0; i < numPixels; i++) {
		pixelData[i * 3 + 0] = raster[i].r;
		pixelData[i * 3 + 1] = raster[i].g;
		pixelData[i * 3 + 2] = raster[i].b;
	}

	glDrawPixels(resolutionX, resolutionY, GL_RGB, GL_FLOAT, pixelData);
	delete pixelData;

	glutSwapBuffers();
}

void saveAsPPM(std::string filename, int resolutionX, int resolutionY, Colour *raster);

int main(int argc, char *argv[]) {
	// setup window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(resolutionX, resolutionY);
	glutCreateWindow("Ray Tracer");

	// tell GLUT about our event-handler functions
	glutIdleFunc(update);
	glutDisplayFunc(display);

	scene = new Scene();

	raster = new Colour[resolutionX * resolutionY];

	glutMainLoop();

	delete raster;

	return 0;
}
