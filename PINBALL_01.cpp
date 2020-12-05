//result:정답
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double PI = 2.0 * acos(0.0);

struct vector2 {
	double x, y;
	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}

	double norm() const { return hypot(x, y); }
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}
	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const vector2& rhs) const {
		return x * rhs.y - rhs.x * y;
	}
	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

const double EPSILON = 1e-9;
const double INFTY = 1e200;

vector<double> solve2(double a, double b, double c) {
	double d = b * b - 4 * a * c;

	if (d < -EPSILON) return vector<double>();

	if (d < EPSILON) return vector<double>(1, -b / (2 * a));
	vector<double> ret;
	ret.push_back((-b - sqrt(d)) / (2 * a));
	ret.push_back((-b + sqrt(d)) / (2 * a));
	return ret;
}

double hitCircle(vector2 here, vector2 dir, vector2 center, int radius) {
	double a = dir.dot(dir);
	double b = 2 * dir.dot(here - center);
	double c = center.dot(center) + here.dot(here) - 2 * here.dot(center) - radius * radius;
	vector<double> sols = solve2(a, b, c);
	if (sols.empty() || sols[0] < EPSILON) return INFTY;
	return sols[0];
}

vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
	return (dir - dir.project(contact - center) * 2).normalize();
}
int n;
vector2 center[50];
int radius[50];
void simulate(vector2 here, vector2 dir) {
	dir = dir.normalize();
	int hitCount = 0;
	while (hitCount < 100) {
		int circle = -1;
		double time = INFTY * 0.5;
		for (int i = 0; i < n; i++) {
			double cand = hitCircle(here, dir, center[i], radius[i] + 1);
			if (cand < time) {
				time = cand;
				circle = i;
			}
		}
		if (circle == -1) break;
		if (hitCount++) cout << " ";
		cout << circle;
		vector2 contact = here + dir * time;
		dir = reflect(dir, center[circle], contact);
		here = contact;
	}
	cout << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test_case;
	cin >> test_case;
	while (test_case--) {
		vector2 here, dir;
		cin >> here.x >> here.y >> dir.x >> dir.y >> n;
		for (int i = 0; i < n; i++) {
			cin >> center[i].x >> center[i].y >> radius[i];
		}
		simulate(here, dir);
	}
}