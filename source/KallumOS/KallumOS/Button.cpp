#include "olcPixelGameEngine.h"
#include "Button.h"
#include "Point.h"

#include <string>


Button::Button(olc::PixelGameEngine* _window, Point _position, Point _size, std::string _value) : Control(_window, _position, _size) {

	color = olc::WHITE;
	value = _value;
}

void Button::Draw() {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(window->ScreenWidth(), window->ScreenHeight()));

	window->FillRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), color);

	if (focused)
		window->DrawRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), olc::BLACK);
}

bool Button::Hover(Point* mousePosition) {

	if (Within(mousePosition)) {

		color = olc::GREY;
		return true;
	}

	color = olc::WHITE;
	return false;
}

bool Button::Click(Point* mousePosition) {

	if (Within(mousePosition)) {
		InvertClicked();
		return true;
	}

	return false;
}

bool Button::GetClicked() {
	return clicked;
}


void Button::InvertClicked() {
	clicked = !clicked;
}