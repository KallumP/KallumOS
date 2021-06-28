#pragma once
#include "olcPixelGameEngine.h"
#include "Point.h"

class Control {

protected:

	Point position;
	Point size;

public:
	Control(Point, Point);

	virtual void Draw(olc::PixelGameEngine*) = 0;
	virtual bool Hover(Point*) = 0;
	virtual bool Click(Point*) = 0;

	bool Within(Point*);


};

