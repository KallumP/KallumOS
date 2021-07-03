#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"

Control::Control(olc::PixelGameEngine* _window, Point _position, Point _size) {
	window = _window;

	//takes position values as percentages
	position = _position;
	size = _size;
	focused = false;
}

//turns a percentage position point into a pixel position point
Point Control::normalizePosition(Point* screenSize) {
	float newX = (screenSize->GetX() * position.GetX()) - size.GetX() / 2;
	float newY = (screenSize->GetY() * position.GetY()) - size.GetY() / 2;

	return Point(newX, newY);
}

//returns if the input point is within this control's hitbox
bool Control::Within(Point* mousePosition) {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(window->ScreenWidth(), window->ScreenHeight()));

	//checks if the mousex is bigger than the positionx and smaller than the positoinx+sizex
	//checks if the mousey is bigger than the positiony and smaller than the positoiny+sizey
	if (mousePosition->GetX() > normalizedPosition->GetX() && mousePosition->GetX() < normalizedPosition->GetX() + size.GetX() &&
		mousePosition->GetY() > normalizedPosition->GetY() && mousePosition->GetY() < normalizedPosition->GetY() + size.GetY())
		return true;

	return false;
}

void Control::InvertFocus() {
	focused = !focused;
}

bool Control::Hover(Point* mousePosition) {

	if (Within(mousePosition)) {

		backColor = hoverColor;
		return true;
	}

	backColor = defaultColor;
	return false;
}