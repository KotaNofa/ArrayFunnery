#define _USE_MATH_DEFINES
#include "Screen.h"
#include "globals.h"
#include <cmath>
#include <iostream>

float CFOVX(float fov) {
	float rads = fov * (M_PI / 180);  // Convert FOV to radians
	float focalLength = height / (2.0 * tan(rads / 2.0));  // Focal length for vertical FOV
	return focalLength * (width / height);  // Scale by aspect ratio (width / height) for X-axis
};

// Calculate FOV for Y
float CFOVY(float fov) {
	float rads = fov * (M_PI / 180);  // Convert FOV to radians
	return height / (2.0 * tan(rads / 2.0));  // Focal length for vertical FOV
};

Screen::Screen()
{
	float fov = 45;

	fovX = CFOVX(fov);
	fovY = CFOVY(fov);
	screenX = width / 2;
	screenY = height / 2;

	X = 0;
	Y = 0;
	Z = 0;
	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;

}

// Convert X To Screen Space
float CTSSX(float in) {
	float out = width / 2 + in;
	return out;
}

// Convert Y To Screen Space
float CTSSY(float in) {
	float out = height / 2 - in;
	return out;
}	

void Screen::DrawVert(Vertex in)
{
	screenX = (CTSSX(in.GetX()));
	screenY = (CTSSY(in.GetY()));
	std::cout << in.GetX() << " " << in.GetY() << std::endl;
	std::cout << screenX << " " << screenY << std::endl;

	DrawRectangle(screenX, screenY, 5, 5, RED);
}

void Screen::XRotation(float degrees)
{

}

void Screen::YRotation(float degrees)
{

}	

void Screen::ZRotation(float degrees)
{

}

void Screen::XTranslate(float amount)
{
	X += amount;
	screenX -= amount;
}

void Screen::YTranslate(float amount)
{
	Y += amount;
	screenY -= amount;
}

void Screen::ZTranslate(float amount)
{
	Z += amount;
}
