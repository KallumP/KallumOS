#pragma once
#include "Process.h"


class TextEditor : public Process {

public:

	TextEditor();
	TextEditor(Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);
private:

	void Input(std::string input);
	void DeleteChar();

	std::string text;

	int cursor;
};

