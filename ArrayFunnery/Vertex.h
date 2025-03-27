#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

class Vertex {
public:

	Vertex();
	Vertex(float inX, float inY, float inZ);
	float GetX();
	float GetY();
	float GetZ();
	void XRotation(float degrees);
	void YRotation(float degrees);
	void ZRotation(float degrees);
	void XTranslate(float amount);
	void YTranslate(float amount);
	void ZTranslate(float amount);

private:
	float X;
	float Y;
	float Z;
};

class Cube {
public:

	std::vector<Vertex> vertList;

	Cube();
	void XRotation(float degrees);
	void YRotation(float degrees);
	void ZRotation(float degrees);
	void XTranslate(float amount);
	void YTranslate(float amount);
	void ZTranslate(float amount);

};


#endif // !3D
