#include "raylib.h"
#include "Button.h"
#include "Point.h"
#include "InputPress.h"

#include <string>


Button::Button(Point _position, Point _size, std::string _value) : Control(_position, _size) {

	clicked = false;
	defaultColor = WHITE;
	hoverColor = GRAY;
	backColor = defaultColor;

	fontColor = BLACK;

	value = _value;

	padding = Point(10, 10);
	fontSize = 2;
}

void Button::Draw() {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(GetScreenWidth(), GetScreenHeight()));

	//draws the button
	DrawRectangle(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), backColor);

	//draws the textbox value
	DrawText(value.c_str(), normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);

	//draws the focus outline
	if (focused)
		DrawRectangle(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), BLACK);
}

bool Button::Click(Point* mousePosition) {

	if (Within(mousePosition)) {
		InvertClicked();
		return true;
	}

	return false;
}

//Keypress event
void Button::OnKeyPress(KeyPress* e) {
}

bool Button::GetClicked() {
	return clicked;
}


void Button::InvertClicked() {
	clicked = !clicked;
}