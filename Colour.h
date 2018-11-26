#ifndef COLOUR_H
#define COLOUR_H

class Colour {
public:
	float r;
	float g;
	float b;
	float a;

	Colour() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
	Colour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

	Colour operator*(const float rhs);
	Colour operator+(const Colour rhs);
};

#endif
