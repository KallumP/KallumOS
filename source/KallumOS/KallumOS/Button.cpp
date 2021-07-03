#include "olcPixelGameEngine.h"
#include "Button.h"
#include "Point.h"

#include <string>


Button::Button(olc::PixelGameEngine* _window, Point _position, Point _size, std::string _value) : Control(_window, _position, _size) {

	defaultColor = olc::WHITE;
	hoverColor = olc::GREY;
	backColor = defaultColor;

	fontColor = olc::BLACK;

	value = _value;

	padding = Point(10, 10);
	fontSize = 2;
}

void Button::Draw() {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(window->ScreenWidth(), window->ScreenHeight()));

	//draws the button
	window->FillRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), backColor);

	//draws the textbox value
	window->DrawString(normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), value, fontColor, fontSize);


	if (focused)

		//draws the focus outline
		window->DrawRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), olc::BLACK);
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