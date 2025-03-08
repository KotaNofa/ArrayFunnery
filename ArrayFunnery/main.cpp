#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int rows = 300;
const int cols = 300;

string screen1[rows][cols];

pair<int, int> point(80, 80);

int originrow(int index) {

	return (rows / 2) - index;

}

int origincol(int index) {

	return (cols / 2) + index;
}

void rotate(pair<int, int>& coords) {
    double angle = 3 * (M_PI / 180.0);  // Rotation by 1 degree
    int x = coords.second;
    int y = coords.first;
    coords.second = static_cast<int>(x * cos(angle) - y * sin(angle));
    coords.first = static_cast<int>(x * sin(angle) + y * cos(angle));
}


int main() {

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			screen1[i][j] = " .";
		}
	}

	screen1[origincol(0)][originrow(0)] = " o";

	cout << "start frame, press enter" << endl;
	while (cin.get()) {
		rotate(point);
		screen1[originrow(point.first)][origincol(point.second)] = " 0";
		cout << "point x" << point.second << endl;
		cout << "point y" << point.first << endl;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				cout << screen1[i][j];
			}
			cout <<  endl;
		}

		cout << "end frame, press enter" << endl;

		

	}

	return 0;
}