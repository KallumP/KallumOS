#pragma once
#include "raylib.h"

#include "Control.h"
#include "Point.h"


#include <string>
#include <vector>

class TextBox : public Control {

public:

	TextBox(Point _position, Point _size, std::string _value, std::string _placeholder);

	void SetObfuscation(std::string);
	void Draw();
	bool Click(Point*);
	void OnKeyPress(KeyPress*);

	std::string GetValue();
	void InvertFocus(bool);


private:

	void Input(std::string input);
	void DeleteOne();
	void DeleteWord();
	void FindNewCursorPosition(int);
	void MoveCursor(int);

	int cursor;
	std::string placeholder;
	std::string obfuscation;
};


