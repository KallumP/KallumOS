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
	void MoveCursor(int toMove) { cursor += toMove; }

	void Run();
	std::vector<std::string> Split(std::string toSplit, std::string delimeter);

	int fontSize;
	std::string text;

	std::vector<std::string> console;
	int consoleHeight;

	int cursor;


};

