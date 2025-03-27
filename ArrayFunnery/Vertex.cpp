#define _USE_MATH_DEFINES
#include <cmath>
#include "vertex.h"
#include "raylib.h"
#include "globals.h"

Vertex::Vertex() {
	X = 0.0;
	Y = 0.0;
	Z = 0.0;

}

Vertex::Vertex(float inX, float inY, float inZ) {

	X = inX;
	Y = inY;
	Z = inZ;
	float price{ 1.5 };
}

float Vertex::GetX()
{
	return X;
}

float Vertex::GetY()
{
	return Y;
}

float Vertex::GetZ()
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

Cube::Cube()
{
	vertList.push_back(Vertex(100, 100, 100));
	vertList.push_back(Vertex(100, -100, 100));
	vertList.push_back(Vertex(-100, -100, 100));
	vertList.push_back(Vertex(-100, 100, 100));
	vertList.push_back(Vertex(100, 100, -100));
	vertList.push_back(Vertex(100, -100, -100));
	vertList.push_back(Vertex(-100, -100, -100));
	vertList.push_back(Vertex(-100, 100, -100));
}

void Cube::XRotation(float degrees)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].XRotation(degrees);
	}
}

void Cube::YRotation(float degrees)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].YRotation(degrees);
	}
}

void Cube::ZRotation(float degrees)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].ZRotation(degrees);
	}
}

void Cube::XTranslate(float amount)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].XTranslate(amount);
	}
}

void Cube::YTranslate(float amount)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].YTranslate(amount);
	}
}

void Cube::ZTranslate(float amount)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].ZTranslate(amount);
	}
}