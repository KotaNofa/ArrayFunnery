#ifndef	SCREEN_H
#define SCREEN_H

#include "raylib.h"

class Screen {
public:
	Vector3 coord;
	Vector3 rotation;
	Vector2 screen;
	double fov;

	Screen(double fov);
	void XRotation(double degrees);
	void YRotation(double degrees);
	void ZRotation(double degrees);
	void XTranslate(double amount);
	void YTranslate(double amount);
	void ZTranslate(double amount);
};

#endif // !CAMERA_H