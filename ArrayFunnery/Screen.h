#ifndef	SCREEN_H
#define SCREEN_H

#include "raylib.h"
#include "Vertex.h"

class Screen {
public:

	float fovX;
	float fovY;
	float screenX;
	float screenY;

	float X;
	float Y;
	float Z;

	float rotationX;
	float rotationY;
	float rotationZ;

	Screen();
	void DrawVert(Vertex in);
	void XRotation(float degrees);
	void YRotation(float degrees);
	void ZRotation(float degrees);
	void XTranslate(float amount);
	void YTranslate(float amount);
	void ZTranslate(float amount);
};

#endif // !CAMERA_H