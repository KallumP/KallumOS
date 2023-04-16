#pragma once
#include "raylib.h"

#include "Point.h" 
#include "InputPress.h"


class Control {

protected:

	Point position;
	Point size;
	bool focused;

	Color hoverColor;
	Color defaultColor;
	Color backColor;

	std::string value;
	Color fontColor;
	Color fadedFontColor;
	Point padding;
	int fontSize;


public:

	Control();
	Control(Point _position, Point _size);

	virtual void Draw() {}
	virtual void Draw(Point offset) {}
	virtual bool Hover(Point* mousePosition);
	virtual bool Click(Point* mousePosition) = 0;
	virtual void OnKeyPress(KeyPress* e) {}


	Point normalizePosition(Point* screenSize);
	bool Within(Point* mousePosition);
	virtual void InvertFocus(bool click);
};

