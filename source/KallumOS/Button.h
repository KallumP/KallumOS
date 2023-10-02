#pragma once
#include "raylib.h"

#include "Control.h"
#include "Point.h"
#include "InputPress.h"

#include <string>

class Button : public Control {

public:
	Button() {}
	Button(Point _position, Point _size, std::string _value);

	void Draw(Point offset = Point(0,0));
	bool OnMousePress(MousePress* e);
	void OnKeyPress(KeyPress* e);

	bool GetClicked();
	void InvertClicked();
	

private:

	bool clicked;

};
