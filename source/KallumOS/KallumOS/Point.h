#pragma once
#include <String>

class Point {

public:

	Point() {
		x = 0;
		y = 0;
	};

	Point(float _x, float _y) {
		x = _x;
		y = _y;
	}

	float GetX() {
		return x;
	}

	float GetY() {
		return y;
	}

	void Set(Point* _new) {
		this->x = _new->x;
		this->y = _new->y;
	}

	void SetX(float _x) {
		x = _x;
	}

	void SetY(float _y) {
		y = _y;
	}

	//returns if the input point is different from this point
	bool Different(Point* compare) {

		if (this->x != compare->x || this->y != compare->y)
			return true;
		return false;
	}

	std::string ToString() {
		std::string toReturn = "";
		toReturn += "X = ";
		toReturn += std::to_string(x);

		toReturn += ", Y = ";
		toReturn += std::to_string(y);

		return toReturn;
	}

private:
	float x;
	float y;
};

