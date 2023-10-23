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

	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);

private:

	void DrawTextInput(Point offset);
	void DrawConsole(Point offset);
	int GetNextLineY(int lineCount) { return (lineCount * MeasureText("X", defaultFontSize) * 4); }

	void NewStatement();
	void SwitchStatement(int amount);
	void Input(std::string input);
	void Delete();
	void DeleteChar();
	void DeleteStatement();
	void MoveCursor(int toMove) { cursor += toMove; }

	void SetupSupportedSymbols();
	void SetupSupportedOpcodes();

	void Run();
	void HandleStatement(std::string statement, int statementNumber);
	std::string CheckOpcode(std::vector<std::string> chunks);
	void HandleOpEmpty(int statementNumber);
	void HandleOpError(int statementNumber);
	void HandleOpNoOp(int statementNumber);
	void HandleOpOut(int statementNumber, std::vector<std::string> chunks);
	void HandleOpInt(int statementNumber, std::vector<std::string> chunks);
	void HandleOpAssign(int statementNumber, std::vector<std::string> chunks);
	
	bool VariableExists(std::string toCheck);
	Variable* GetVariable(std::string toGet);
	bool ValidFunction(std::vector<std::string> chunks, int startIndex);
	std::string HandleFunction(int statementNumber, std::vector<std::string> chunks, int startIndex);
	void AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor);

	int Add(int a, int b) { return a + b; }
	int Minus(int a, int b) { return a - b; }
	int Multiply(int a, int b) { return a * b; }
	int Divide(int a, int b) { return a / b; }
	int Exponent(int a, int b) { return  std::pow(a, b); }

	int fontSize;

	int cursor;
	int statementFocus;
	std::vector<std::string> statements;
	std::vector<Variable*> variables;
	std::vector<std::string> supportedSymbols;
	std::vector<std::string> supportedOpCodes;

	std::vector<ConsoleText> console;
	int consoleHeight;
	bool debug;
};

