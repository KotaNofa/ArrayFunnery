#define _USE_MATH_DEFINES
#include "Screen.h"
#include "globals.h"
#include <cmath>
#include <iostream>
#include "Object.h"

// Calculate Field Of View
float Screen::CalculateFOV(float fovDegrees) {
	float fovRadians = fovDegrees * (M_PI / 180.0f);
	return 1 / tan(fovRadians / 2);
}
// Convert X To Screen Space
float Screen::CTSSX(float in) {
	return (width / 2.0f) + (in * width / 2.0f);
}
// Convert Y To Screen Space
float Screen::CTSSY(float in) {
	return (height / 2.0f) - (in * height / 2.0f);
}

Screen::Screen()
{
	fovX = CalculateFOV(84);
	fovY = fovX * (width / height);

	X = 0;
	Y = 0;
	Z = 0;

	rX = 0;
	rY = 0;
	rZ = 0;

}

void Screen::SetFOV(float degrees)
{
	fovX = CalculateFOV(degrees);
	fovY = fovX * (width / height);
}

void Screen::XRotation(float degrees)
{
	rX += fmod(degrees, 360.0f);
	if (rX < 0) rX += 360.0f;
}

void Screen::YRotation(float degrees)
{
	rY += fmod(degrees, 360.0f);
	if (rY < 0) rY += 360.0f;
}	

void Screen::ZRotation(float degrees)
{
	rZ += fmod(degrees, 360.0f);
	if (rZ < 0) rZ += 360.0f;
}

void Screen::XTranslate(float amount)
{
	X += amount;
}

void Screen::YTranslate(float amount)
{
	Y += amount;
}

void Screen::ZTranslate(float amount)
{
	Z += amount;
}

void Screen::DrawVerts(Object& in)
{

}