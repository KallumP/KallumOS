#include "olcPixelGameEngine.h"
#include "TextBox.h"
#include "Point.h"
#include "KeyPress.h"

#include <string>
#include <iostream>

TextBox::TextBox(olc::PixelGameEngine* _window, Point _position, Point _size, std::string _value) : Control(_window, _position, _size) {

	defaultColor = olc::WHITE;
	hoverColor = olc::GREY;
	backColor = defaultColor;

	fontColor = olc::BLACK;

	padding = Point(10, 10);
	fontSize = 2;

	value = _value;
	cursorPosition = 0;
}

void TextBox::Draw() {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(window->ScreenWidth(), window->ScreenHeight()));

	//draws the text box
	window->FillRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), backColor);

	//draws the textbox value
	window->DrawString(normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), value, fontColor, fontSize);

	if (focused) {

		//draws the focus outline
		window->DrawRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), olc::BLACK);

		//draws the cursor
		window->DrawLine(
			normalizedPosition->GetX() + padding.GetX() + (cursorPosition)*fontSize * 8,
			normalizedPosition->GetY() + padding.GetY(),
			normalizedPosition->GetX() + padding.GetX() + (cursorPosition)*fontSize * 8,
			normalizedPosition->GetY() + size.GetY() - padding.GetY(),
			fontColor);
	}

}

bool TextBox::Click(Point* mousePosition) {

	if (Within(mousePosition)) {
		FindNewCursorPosition(mousePosition->GetX());
		return true;
	}

	return false;
}

//Keypress event
void TextBox::OnKeyPress(KeyPress* e) {

	std::cout << "Press detected. ";
}

void TextBox::FindNewCursorPosition(int mouseX) {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(window->ScreenWidth(), window->ScreenHeight()));

	//loops through each of the characters in the string
	for (int i = 0; i < value.size(); i++) {

		//checks if the click was behind the next character
		if (mouseX < normalizedPosition->GetX() + padding.GetX() + (i + 1) * fontSize * 8) {
			cursorPosition = i;
			return;
		}
	}

	//if no position was found, then it just sets the cursor to the end
	cursorPosition = value.size();
}

void TextBox::Append(char input) {

}
void TextBox::DeleteOne() {

}
void TextBox::DeleteWord() {

}