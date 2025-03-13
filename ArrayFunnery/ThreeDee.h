#ifndef THREEDEE_H
#define THREEDEE_H

#include <vector>

class ThreeDee {
public:

	double X;
	double Y;
	double Z;
	int Xindex;
	int Yindex;

	ThreeDee();
	ThreeDee(double inX, double inY, double inZ);
	void DrawPoint(int size);
	void XRotation(double degrees);
	void YRotation(double degrees);
	void ZRotation(double degrees);
	void XTranslate(double amount);
	void YTranslate(double amount);
	void ZTranslate(double amount);
};

class Cube : public ThreeDee {
public:

	std::vector<ThreeDee> vertList;

	Cube();
	void DrawCubePoints(int size);
	void DrawCubeLines();
	void XRotation(double degrees);
	void YRotation(double degrees);
	void ZRotation(double degrees);
	void XTranslate(double amount);
	void YTranslate(double amount);
	void ZTranslate(double amount);

};


#endif // !3D
