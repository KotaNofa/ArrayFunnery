#ifndef THREEDEE_H
#define THREEDEE_H

class ThreeDee {
public:

	double X;
	double Y;
	double Z;
	int Xindex;
	int Yindex;

	ThreeDee(double inX, double inY, double inZ);
	void Draw();
	void XRotation(double degrees);
	void YRotation(double degrees);
	void ZRotation(double degrees);
	void XTranslate(double amount);
	void YTranslate(double amount);
	void ZTranslate(double amount);
};

#endif // !3D
