#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:

	Vertex();
	Vertex(float inX, float inY, float inZ);
	float GetX() const;
	float GetY() const;
	float GetZ() const;
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

#endif
