#pragma once
#include "Process.h"

#include <vector>

class Kode : public Process {

public:
	Kode();
	Kode(Point _position, Point _size);

	void Draw(Point offset);
	void DrawTextInput(Point offset);
	void DrawConsole(Point offset);

	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);
	void Tick(float elapsedTime) {

	}

private:

	void Input(std::string input);
	void DeleteChar();

	void Run();

	int fontSize;
	std::string text;

	std::vector<std::string> console;
	int consoleHeight;

	int cursor;


};

