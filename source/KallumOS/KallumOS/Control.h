#pragma once
#include "olcPixelGameEngine.h"
#include "Point.h"

class Control {

protected:

	Point position;
	Point size;
	olc::PixelGameEngine* window;
	bool focused;

public:

	Control(olc::PixelGameEngine*, Point, Point);

	virtual void Draw() = 0;
	virtual bool Hover(Point*) = 0;
	virtual bool Click(Point*) = 0;

	Point normalizePosition(Point*);
	bool Within(Point*);
	void RevertFocus();

};

