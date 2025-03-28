#ifndef	SCREEN_H
#define SCREEN_H

#include "raylib.h"
#include "Vertex.h"

class Screen {
private:
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

	float CalculateFOV(float degrees);
	float CTSSX(float in);
	float CTSSY(float in);

public:
	Screen();
	void SetFOV(float degrees);
	void XRotation(float degrees);
	void YRotation(float degrees);
	void ZRotation(float degrees);
	void XTranslate(float amount);
	void YTranslate(float amount);
	void ZTranslate(float amount);
	void DrawVert(Vertex in);
	void DrawVertCube(Cube);
};

#endif // !CAMERA_H