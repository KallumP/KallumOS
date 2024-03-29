#include "raylib.h"
#include "kGraphics.h"

#include "TextBox.h"
#include "Point.h"
#include "InputPress.h"
#include "Helper.h"

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
	singleCharWidth = fontSize * 0.7;

	value = _value;
	placeholder = _placeholder;

	cursor = 0;
}

void TextBox::SetObfuscation(std::string _obfuscation) {
	obfuscation = _obfuscation;
}

void TextBox::Draw(Point offset) {

	Point* normalizedPosition = GetPosition();

	//draws the text box
	kGraphics::FillRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), backColor);

	if (value != "")

		if (obfuscation == "") {

			//draws the textbox value
			kGraphics::DrawString(value, normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);
		} else {

			std::string obfuscatedString;
			for (int i = 0; i < value.size(); i++)
				obfuscatedString.append(obfuscation);

			kGraphics::DrawString(obfuscatedString, normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);
		}

	else
		kGraphics::DrawString(placeholder, normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);

	if (focused) {

		//draws the focus outline
		kGraphics::DrawRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), BLACK);

		int textWidthToCursor = 0;
		if (value.length() > 0)
			textWidthToCursor = MeasureText(value.substr(0, cursor).c_str(), fontSize);

		//draws the cursor
		kGraphics::kDrawLine(
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

	if (e->GetKeyCode() == KEY_BACKSPACE) {
		DeleteOne(true);
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

	Point normMouse = Helper::NormaliseMousePos(*GetPosition());

	//loops through each of the characters in the string
	for (int i = 0; i < value.size(); i++) {

		//checks if the click was behind the next character
		if (normMouse.GetX() < singleCharWidth * i) {
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
}

void TextBox::DeleteOne(bool backward) {
	if (value.length() != 0) {

		if (backward) {

			if (cursor != 0) {

				//value.pop_back();
				value.erase(cursor - 1, 1);

				MoveCursor(-1);
			}

		} else {

			if (cursor != value.length()) {

				//value.pop_back();
				value.erase(cursor + 1, 1);

				MoveCursor(-1);
			}
		}
	}
}

void TextBox::DeleteWord() {

}

std::string TextBox::GetValue() {
	return value;
}

void TextBox::SetValue(std::string _value) {
	value = _value;
}

void TextBox::InvertFocus() {
	focused = !focused;
}