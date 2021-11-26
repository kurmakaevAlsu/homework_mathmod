#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

struct Point {
	double x = 0, y = 0;
};


double distance(const Point& point1, const Point& point2, const Point& obj) {

	double result;
	double dy = point2.y - point1.y;
	double dx = point2.x - point1.x;

	if (abs(dy) < 0.00000001 && abs(dx) < 0.00000001)
		return 0;
	result = (dy * obj.x - dx * obj.y + point2.x * point1.y - point2.y * point1.x);
	result /= sqrt(dx * dx + dy * dy);

	return result;
}

int main() {
	vector<Point> points;
	Point start{ 0, 0 };
	Point vec;
	string input = "in.txt";
	ifstream cin(input);

	cin >> vec.x >> vec.y;

	while (!cin.eof()) {
		Point cur;
		cin >> cur.x >> cur.y;
		points.push_back(cur);
	}

	Point left, right;
	double min = 0.0, max = 0.0;

	for (int i = 0; i < points.size(); i++) {
		double dist = distance(start, vec, points[i]);

		if (min >= dist) {
			min = dist;
			left = points[i];
		}

		if (max <= dist) {
			max = dist;
			right = points[i];
		}
	}

	cout << "Leftmost: " << left.x << " " << left.y << endl;
	cout << "Rightmost: " << right.x << " " << right.y << endl;


	return 0;
}
