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

	void Add(Point p) {
		SetX(GetX() + p.GetX());
		SetY(GetY() + p.GetY());
	}

	//returns if the input point is different from this point
	bool Different(Point* compare) {

		if (this->x != compare->x || this->y != compare->y)
			return true;
		return false;
	}

	//returns the difference between this point and the passed point
	Point Difference(Point p) {

		Point toReturn;

		toReturn.SetX(GetX() - p.GetX());
		toReturn.SetY(GetY() - p.GetY());

		return toReturn;
	}

	//returns a string of this point
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

