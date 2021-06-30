#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"

#include <string>

class Button : public Control
{

public:

	Button(olc::PixelGameEngine*, Point, Point, std::string);

	void Draw();
	bool Hover(Point*);
	bool Click(Point*);

private:

	std::string value;
	olc::Pixel color;

};
