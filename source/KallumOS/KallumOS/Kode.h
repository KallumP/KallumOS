#pragma once
#include "Process.h"

class Kode : public Process {

public:
	Kode();
	Kode(Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);
	void Tick(float elapsedTime) {

	}

private:

	void Input(std::string input);
	void DeleteChar();

	int fontSize;
	std::string text;

	int cursor;


};

