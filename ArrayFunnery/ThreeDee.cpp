#define _USE_MATH_DEFINES
#include <cmath>
#include "ThreeDee.h"
#include "raylib.h"

ThreeDee::ThreeDee(double inX, double inY, double inZ) {

	X = inX;
	Y = inY;
	Z = inZ;

	Xindex = 1080 / 2 + X;
	Yindex = 1080 / 2 - Y;

}

void ThreeDee::Draw() {


	float FOV = 300;
	float ZNear = 1.0f;

	float Zclamped = (Z < ZNear) ? ZNear : Z;

	float Xproj = (X / Zclamped) * FOV;
	float Yproj = (Y / Zclamped) * FOV;

	Xindex = 1080 / 2 + Xproj;
	Yindex = 1080 / 2 - Yproj;

	DrawCircle(Xindex, Yindex, 10, BLACK);

}

void ThreeDee::XRotation(double degrees) {
	double radians = degrees * (M_PI / 180);

	double tempY = Y * cos(radians) - Z * sin(radians);
	double tempZ = Y * sin(radians) + Z * cos(radians);


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
	Z = tempZ;

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
