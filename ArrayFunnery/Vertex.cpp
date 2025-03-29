#define _USE_MATH_DEFINES
#include <cmath>
#include "globals.h"
#include "vertex.h"
#include "Object.h"

Vertex::Vertex() {

	X = 0.0;
	Y = 0.0;
	Z = 0.0;
}

Vertex::Vertex(float inX, float inY, float inZ) {

	X = inX;
	Y = inY;
	Z = inZ;
}

float Vertex::GetX() const
{
	return X;
}

float Vertex::GetY() const
{
	return Y;
}

float Vertex::GetZ() const
{
	return Z;
}

void Vertex::XRotation(float degrees) {
	float radians = degrees * (M_PI / 180);

	float tempY = Y * cos(radians) - Z * sin(radians);
	float tempZ = Y * sin(radians) + Z * cos(radians);

	Y = tempY;
	Z = tempZ;
}

void Vertex::YRotation(float degrees) {
	float radians = degrees * (M_PI / 180);

	float tempX = X * cos(radians) + Z * sin(radians);
	float tempZ = -X * sin(radians) + Z * cos(radians);

	X = tempX;
	Z = tempZ;

}
void Vertex::ZRotation(float degrees) {
	float radians = degrees * (M_PI / 180);

	float tempX = X * cos(radians) - Y * sin(radians);
	float tempY = X * sin(radians) + Y * cos(radians);
	float tempZ = Z;

	X = tempX;
	Y = tempY;

}

void Vertex::XTranslate(float amount)
{
	X += amount;
}

void Vertex::YTranslate(float amount)
{
	Y += amount;
}

void Vertex::ZTranslate(float amount)
{
	Z += amount;
}