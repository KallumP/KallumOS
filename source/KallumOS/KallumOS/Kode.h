#pragma once
#include "Process.h"

#include <vector>


struct Variable {
	std::string identifier;
	std::string value;
	std::string type;
};

struct ConsoleText {

	std::string text;
	Color textColor;
	int linkedToStatement;
};

class Kode : public Process {

public:
	Kode();
	Kode(Point _position, Point _size);

	void Draw(Point offset);
	void DrawTextInput(Point offset);
	void DrawConsole(Point offset);

	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);
	void Tick(float elapsedTime) {}

private:

	void Input(std::string input);
	void DeleteChar();
	void MoveCursor(int toMove) { cursor += toMove; }

	std::vector<std::string> Split(std::string toSplit, std::string delimeter);
	int GetNextLineY(int lineCount) { return (lineCount * MeasureText("X", defaultFontSize) * 4); }

	void Run();
	std::string CheckOpcode(std::vector<std::string> chunks);
	void AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor);
	bool VariableExists(std::string toCheck);
	Variable* GetVariable(std::string toGet);
	bool Intable(std::string toCheck);

	int fontSize;
	std::string text;
	int cursor;

	std::vector<ConsoleText> console;
	int consoleHeight;
	bool debug;


	std::vector<Variable*> variables;

};

