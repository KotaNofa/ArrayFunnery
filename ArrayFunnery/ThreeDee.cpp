#define _USE_MATH_DEFINES
#include <cmath>
#include "ThreeDee.h"
#include "raylib.h"
#include "globals.h"

ThreeDee::ThreeDee() {
	X = 0.0;
	Y = 0.0;
	Z = 0.0;
	Xindex = width / 2 + X;
	Yindex = height / 2 - Y;
}

ThreeDee::ThreeDee(double inX, double inY, double inZ) {

	X = inX;
	Y = inY;
	Z = inZ;

	Xindex = width / 2 + X;
	Yindex = height / 2 - Y;

}

void ThreeDee::DrawPoint(int size)
{
	float FOV = 500;
	float ZNear = 1.0f;

	float Zclamped = (Z < ZNear) ? ZNear : Z;

	float Xproj = (X / Zclamped) * FOV;
	float Yproj = (Y / Zclamped) * FOV;

	Xindex = width / 2 + Xproj;
	Yindex = height / 2 - Yproj;

	DrawCircle(Xindex, Yindex, size, BLACK);
}

void ThreeDee::XRotation(double degrees) {
	double radians = degrees * (M_PI / 180);

	double tempY = Y * cos(radians) - Z * sin(radians);
	double tempZ = Y * sin(radians) + Z * cos(radians);

	Y = tempY;
	Z = tempZ;
}

void ThreeDee::YRotation(double degrees) {
	double radians = degrees * (M_PI / 180);

	double tempX = X * cos(radians) + Z * sin(radians);
	double tempZ = -X * sin(radians) + Z * cos(radians);

	X = tempX;
	Z = tempZ;

}
void ThreeDee::ZRotation(double degrees) {
	double radians = degrees * (M_PI / 180);

	double tempX = X * cos(radians) - Y * sin(radians);
	double tempY = X * sin(radians) + Y * cos(radians);
	double tempZ = Z;

	X = tempX;
	Y = tempY;

}

void ThreeDee::XTranslate(double amount)
{
	X += amount;
}

void ThreeDee::YTranslate(double amount)
{
	Y += amount;
}

void ThreeDee::ZTranslate(double amount)
{
	Z += amount;
}

Cube::Cube()
{
	vertList.push_back(ThreeDee(100, 100, 100));
	vertList.push_back(ThreeDee(100, -100, 100));
	vertList.push_back(ThreeDee(-100, -100, 100));
	vertList.push_back(ThreeDee(-100, 100, 100));
	vertList.push_back(ThreeDee(100, 100, -100));
	vertList.push_back(ThreeDee(100, -100, -100));
	vertList.push_back(ThreeDee(-100, -100, -100));
	vertList.push_back(ThreeDee(-100, 100, -100));
}

void Cube::DrawCubePoints(int size)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].DrawPoint(size);
	}
}

void Cube::DrawCubeLines()
{
	for (int i = 0; i < 8; ++i) {
		if (i < 4) {
			DrawLine(vertList[i % 4].Xindex, vertList[i % 4].Yindex, vertList[(i + 1) % 4].Xindex, vertList[(i + 1) % 4].Yindex, BLACK);
		}
		if (i == 4) {
			for (int j = 0; j < 4; ++j) {
				DrawLine(vertList[(j % 4) + 4].Xindex, vertList[(j % 4) + 4].Yindex, vertList[j % 4].Xindex, vertList[j % 4].Yindex, BLACK);
			}
		}
		if (i < 4) {
			DrawLine(vertList[(i % 4) + 4].Xindex, vertList[(i % 4) + 4].Yindex, vertList[((i + 1) % 4) + 4].Xindex, vertList[((i + 1) % 4) + 4].Yindex, BLACK);
		}
	}

}

void Cube::XRotation(double degrees)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].XRotation(degrees);
	}
}

void Cube::YRotation(double degrees)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].YRotation(degrees);
	}
}

void Cube::ZRotation(double degrees)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].ZRotation(degrees);
	}
}

void Cube::XTranslate(double amount)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].XTranslate(amount);
	}
}

void Cube::YTranslate(double amount)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].YTranslate(amount);
	}
}

void Cube::ZTranslate(double amount)
{
	for (int i = 0; i < 8; ++i) {
		vertList[i].ZTranslate(amount);
	}
}