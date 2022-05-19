#pragma once
#include "raylib.h"

#include "Control.h"
#include "Point.h"
#include "InputPress.h"

#include <string>

class Button : public Control {

public:

	Button(Point _position, Point _size, std::string _value);

	void Draw();
	bool Click(Point* mousePosition);
	void OnKeyPress(KeyPress* e);

	bool GetClicked();
	void InvertClicked();

private:

	bool clicked;

};
