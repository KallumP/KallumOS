#include "raylib.h"
#include "kGraphics.h"
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
	fontSize = 20;
}

void Button::Draw(Point offset) {

	Point* normalizedPosition = GetPosition();

	//draws the button
	kGraphics::FillRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), backColor);

	//draws the textbox value
	kGraphics::DrawString(value, normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);

	//draws the focus outline
	if (focused)
		kGraphics::DrawRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), BLACK);
}

bool Button::OnMousePress(MousePress* e) {

	if (Within(e->GetMousePosition())) {
		InvertClicked();
		return true;
	}

	return false;
}

void Button::OnKeyPress(KeyPress* e) {
}

bool Button::GetClicked() {
	return clicked;
}

void Button::InvertClicked() {
	clicked = !clicked;
}