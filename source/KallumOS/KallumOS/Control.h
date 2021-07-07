#pragma once
#include "olcPixelGameEngine.h"
#include "Point.h"

class Control {

protected:

	Point position;
	Point size;
	olc::PixelGameEngine* window;
	bool focused;

	olc::Pixel hoverColor;
	olc::Pixel defaultColor;
	olc::Pixel backColor;

	std::string value;
	olc::Pixel fontColor;
	Point padding;
	int fontSize;


public:

	Control(olc::PixelGameEngine*, Point, Point);

	virtual void Draw() = 0;
	virtual bool Hover(Point*);
	virtual bool Click(Point*) = 0;
	virtual void KeyboardInput(std::vector<olc::Key>) = 0;

	Point normalizePosition(Point*);
	bool Within(Point*);
	void InvertFocus();

};

