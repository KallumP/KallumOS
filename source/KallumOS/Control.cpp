#include "raylib.h"

#include "Control.h"
#include "Point.h"



Control::Control() {

}

Control::Control(Point _position, Point _size) {

	//takes position values as percentages
	position = _position;
	size = _size;
	focused = false;
	centered = true;
}

//turns a percentage position point into a pixel position point
Point Control::normalizePosition(Point* screenSize) {
	float newX = (screenSize->GetX() * position.GetX()) - size.GetX() / 2;
	float newY = (screenSize->GetY() * position.GetY()) - size.GetY() / 2;

	return Point(newX, newY);
}

//returns if the input point is within this control's hitbox
bool Control::Within(Point* mousePosition) {

	Point* normalizedPosition = GetPosition();

	//checks if the mousex is bigger than the positionx and smaller than the positoinx+sizex
	//checks if the mousey is bigger than the positiony and smaller than the positoiny+sizey
	if (mousePosition->GetX() > normalizedPosition->GetX() && mousePosition->GetX() < normalizedPosition->GetX() + size.GetX() &&
		mousePosition->GetY() > normalizedPosition->GetY() && mousePosition->GetY() < normalizedPosition->GetY() + size.GetY())
		return true;

	return false;
}

void Control::InvertFocus(bool click) {
	focused = !focused;
}

bool Control::OnMouseMove(Point* e) {

	if (Within(e)) {

		backColor = hoverColor;
		return true;
	}

	backColor = defaultColor;
	return false;
}

void  Control::Tether(Point* _tether) {

	centered = !centered;
	tether = _tether;
}

Point* Control::GetPosition() {

	Point* normalizedPosition = new Point();

	//returns the pixel values of the position based on if it should be centered or not
	if (centered)
		*normalizedPosition = normalizePosition(new Point(GetScreenWidth(), GetScreenHeight()));
	else {
		*normalizedPosition = position;
		normalizedPosition->Add(*tether);
	}

	return normalizedPosition;
}