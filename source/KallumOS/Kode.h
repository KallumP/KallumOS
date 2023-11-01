#pragma once
#include "Process.h"

#include <vector>
#include <map>

enum class Instruction { Empty, Error, NoInstruction, Out, Int, Bool, Assign };

enum class VariableType { Int, Bool, String, Null };
struct Variable {
	std::string identifier;
	std::string value;
	VariableType type;
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
	void SetupSupportedInstructions();

	void Run();
	void HandleStatement(std::string statement, int statementNumber);
	Instruction CheckInstruction(std::vector<std::string> chunks);
	Instruction ResolveManualInstruction(std::string input);

	void HandleEmpty(int statementNumber);
	void HandleError(int statementNumber);
	void HandleNoInstruction(int statementNumber);
	void HandleOut(int statementNumber, std::vector<std::string> chunks);
	void HandleInt(int statementNumber, std::vector<std::string> chunks);
	void HandleBool(int statementNumber, std::vector<std::string> chunks);
	void HandleAssign(int statementNumber, std::vector<std::string> chunks);

	bool ValidArithmeticOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);
	std::string ResolveArithmeticOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);
	bool ValidBooleanOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);
	std::string ResolveBooleanOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);

	bool VariableExists(std::string toCheck);
	Variable* GetVariable(std::string toGet);
	void AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor);

	VariableType ChunkType(std::string toCheck);
	std::string BoolToString(bool value) { return value ? "true" : "false"; }

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

	std::vector<std::string> arithmeticOperators;
	std::vector<std::string> booleanOperators;
	std::vector<std::string> booleanComparators;
	std::vector<std::string> notOperators;

	std::map<std::string, Instruction> supportedInstructions;

	std::vector<ConsoleText> console;
	int consoleHeight;
	bool debug;
};

