#define _USE_MATH_DEFINES
#include "Screen.h"
#include "globals.h"
#include <cmath>
#include <iostream>

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
	screenX = CTSSX(0);
	screenY = CTSSY(0);

	X = 0;
	Y = 0;
	Z = 0;

	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;

}

void Screen::SetFOV(float degrees)
{
	fovX = CalculateFOV(degrees);
	fovY = fovX * (width / height);
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
}

void Screen::YTranslate(float amount)
{
	Y += amount;
}

void Screen::ZTranslate(float amount)
{
	Z += amount;
}

void Screen::DrawVert(Vertex in)
{
	float viewX = in.GetX() - X;
	float viewY = in.GetY() - Y;
	float viewZ = in.GetZ() - Z;

	if (viewZ <= 0) return;

	float projectedX = (viewX * fovX) / viewZ;
	float projectedY = (viewY * fovY) / viewZ;

	screenX = CTSSX(projectedX);
	screenY = CTSSY(projectedY);

	if (IsKeyPressed(KEY_F3)) {
		std::cout << "Global Pos " << in.GetX() << " " << in.GetY() << " " << in.GetZ() << std::endl;
		std::cout << "Screen Pos " << screenX << " " << screenY << std::endl;
		std::cout << "Cam Pos " << X << " " << Y << " " << Z << std::endl;
	}

	DrawRectangle(screenX, screenY, 5, 5, RED);
}

void Screen::DrawVertCube(Cube in)
{
	for (int i = 0; i < in.vertList.size(); i++) {
		DrawVert(in.vertList[i]);
	}
}