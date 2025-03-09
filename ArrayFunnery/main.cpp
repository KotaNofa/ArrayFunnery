#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

struct Point
{
	string l;
	double vX;
	double vY;
	double r;
	int iX;
	int iY;
};

Point start;
int width;
int height;
vector<vector<Point*>>screen;
int iterations;

void Init() {

	cout << "Enter X from origin" << endl;
	cin >> start.vX;
	cout << "Enter Y from origin" << endl;
	cin >> start.vY;
	cout << "Enter rotation amount in degrees" << endl;
	cin >> start.r;


	width = 3 * start.vX;
	height = 3 * start.vY;

	if (width < height) {
		width = height;
	}
	else {
		height = width;
	}

	screen.resize(width);
	for (int i = 0; i < width; ++i) {
		screen[i].resize(height);

		for (int j = 0; j < height; ++j) {

			Point* fill = new Point;
			fill->l = ".";

			screen[i][j] = fill;
		}
	}

	Point* origin = new Point;
	origin->l = "0";
	screen[width / 2][height / 2] = origin;

	iterations = M_PI * 2 * height;
}

void computeRotation(Point start, double degrees) {
	double radians = degrees * (M_PI / 180);

	for (int i = 0; i < iterations; ++i) {
		Point* update = new Point;
		update->l = "0";

		double angle = (i * 2 * M_PI) / iterations;

		update->vX = start.vX * cos(angle) - start.vY * sin(angle);
		update->vY = start.vX * sin(angle) + start.vY * cos(angle);

		update->iX = (height / 2) - update->vY;
		update->iY = (width / 2) + update->vX;
		screen[update->iX][update->iY] = update;
	}
}

void printScreen() {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			cout << screen[i][j]->l << " ";
		}
		cout << endl;
	}
}

int main() {

	Init();
	computeRotation(start, start.r);
	printScreen();

	return 0;
}