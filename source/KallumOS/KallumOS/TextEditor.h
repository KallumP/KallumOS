#pragma once

#include "Process.h"


class TextEditor : public Process {

public:

	TextEditor();
	TextEditor(olc::PixelGameEngine* _window, Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);
private:

	void Input(std::string input);
	void DeleteChar();

	std::string text;
	int fontSize;

	int cursor;

};

