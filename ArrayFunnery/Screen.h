#ifndef	SCREEN_H
#define SCREEN_H

#include "Vertex.h"
#include "Object.h"

class Screen {
private:

	float fovX;
	float fovY;

	float X;
	float Y;
	float Z;
	float rX;
	float rY;
	float rZ;

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
	void DrawVerts(Object& in);
	
};

#endif // !CAMERA_H