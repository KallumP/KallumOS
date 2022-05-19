#include "raylib.h"

#include "TextBox.h"
#include "Point.h"
#include "InputPress.h"

#include <string>
#include <iostream>

TextBox::TextBox(Point _position, Point _size, std::string _value, std::string _placeholder) : Control(_position, _size) {

	defaultColor = WHITE;
	hoverColor = GRAY;
	backColor = defaultColor;

	fontColor = BLACK;
	fadedFontColor = DARKGRAY;

	padding = Point(10, 10);
	fontSize = 20;

	value = _value;
	placeholder = _placeholder;

	cursor = 0;
}

void TextBox::SetObfuscation(std::string _obfuscation) {
	obfuscation = _obfuscation;
}

void TextBox::Draw() {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(GetScreenWidth(), GetScreenHeight()));

	//draws the text box
	DrawRectangle(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), backColor);

	if (value != "")

		if (obfuscation == "") {

			//draws the textbox value
			DrawText(value.c_str(), normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);
		} else {

			std::string obfuscatedString;
			for (int i = 0; i < value.size(); i++)
				obfuscatedString.append(obfuscation);

			DrawText(obfuscatedString.c_str(), normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);
		}

	else
		DrawText(placeholder.c_str(), normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);

	if (focused) {

		//draws the focus outline
		DrawRectangleLines(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), BLACK);

		int textWidthToCursor = 0;
		if (value.length() > 0)
			textWidthToCursor = MeasureText(value.substr(0, cursor).c_str(), fontSize);

		//draws the cursor
		DrawLine(
			normalizedPosition->GetX() + padding.GetX() + textWidthToCursor,
			normalizedPosition->GetY() + padding.GetY(),
			normalizedPosition->GetX() + padding.GetX() + textWidthToCursor,
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

void TextBox::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == KEY_BACK) {
		DeleteOne();
		return;
	} else if (e->GetKeyCode() == KEY_LEFT) {
		MoveCursor(-1);
		return;
	} else if (e->GetKeyCode() == KEY_RIGHT) {
		MoveCursor(1);
		return;
	}

	if (e->GetKeyContent().length() != 0)
		Input(e->GetKeyContent());
}

void TextBox::FindNewCursorPosition(int mouseX) {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(GetScreenWidth(), GetScreenHeight()));

	//loops through each of the characters in the string
	for (int i = 0; i < value.size(); i++) {

		//checks if the click was behind the next character
		if (mouseX < singleCharWidth * i) {
			cursor = i;
			return;
		}
	}

	//if no position was found, then it just sets the cursor to the end
	cursor = value.size();
}

void TextBox::MoveCursor(int toMove) {
	cursor += toMove;

	if (cursor < 0)
		cursor = 0;
	else if (cursor > value.length())
		cursor = value.length();
}

void TextBox::Input(std::string input) {

	value.insert(cursor, input);

	MoveCursor(1);;
	std::cout << "Pressed: " << input << std::endl;

}

void TextBox::DeleteOne() {
	if (value.length() != 0) {

		value.pop_back();
		MoveCursor(-1);

		std::cout << "Pressed: Backspace" << std::endl;

	} else {

		std::cout << "Pressed: Backspace; There was nothing to delete" << std::endl;
	}
}

void TextBox::DeleteWord() {

}

std::string TextBox::GetValue() {
	return value;
}

void TextBox::InvertFocus(bool click) {
	focused = !focused;

	if (focused && !click) {
		cursor = value.length();
	}
}