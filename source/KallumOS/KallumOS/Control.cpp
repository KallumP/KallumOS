#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"

Control::Control(Point _position, Point _size) {
	position = _position;
	size = _size;
}

bool Control::Within(Point* mousePosition) {

	//checks if the mousex is bigger than the positionx and smaller than the positoinx+sizex
	//checks if the mouse y is bigger than the positiony and smalle rhtan the positoiny+sizey
	if (mousePosition->GetX() > position.GetX() && mousePosition->GetX() < position.GetX() + size.GetX() &&
		mousePosition->GetY() > position.GetY() && mousePosition->GetY() < position.GetY() + size.GetY())
		return true;

	return false;

}