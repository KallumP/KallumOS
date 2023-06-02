#pragma once
#include "raylib.h"

#include "Control.h"
#include "Point.h"


#include <string>
#include <vector>

class TextBox : public Control {

public:

	TextBox() {}
	TextBox(Point _position, Point _size, std::string _value, std::string _placeholder);

	void SetObfuscation(std::string _obfuscation);
	void Draw(Point offset = Point(0,0));
	bool Click(Point* mousePosition);
	void OnKeyPress(KeyPress* e);

	std::string GetValue();
	void SetValue(std::string _value);
	void InvertFocus(bool click);


private:

	void Input(std::string input);
	void DeleteOne(bool back);
	void DeleteWord();
	void FindNewCursorPosition(int mouseX);
	void MoveCursor(int toMove);

	float singleCharWidth;

	int cursor;
	std::string placeholder;
	std::string obfuscation;
};


