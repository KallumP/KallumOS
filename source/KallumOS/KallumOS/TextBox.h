#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"

#include <string>

class TextBox : public Control {

public:
	TextBox();
	TextBox(Point, Point);

	void Draw(olc::PixelGameEngine*);
	bool Hover(Point*);
	bool Click(Point*);

	void Append(char input);
	void DeleteOne();
	void DeleteWord();

private:

	std::string value;
	olc::Pixel color;

};


