#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"
#include "InputPress.h"

#include <string>

class Button : public Control {

public:

	Button(olc::PixelGameEngine*, Point, Point, std::string);

	void Draw();
	bool Click(Point*);
	void OnKeyPress(KeyPress*);

	bool GetClicked();
	void InvertClicked();

private:

	bool clicked;

};
