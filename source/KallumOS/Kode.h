#pragma once
#include "Process.h"

#include <vector>
#include <map>

enum class Instruction { Empty, Error, NoInstruction, Out, Int, Bool, Assign, If, EndIf, While, EndWhile };
enum class BoolOperator { Null, And, Or };
enum class BoolComparator { Equal, NotEqual, Less, LessEqual, More, MoreEqual };

enum class VariableType { Int, Bool, String, Null };
enum class SegmentType { Main, If, While, Func };

struct Segment {
	Segment(int _start, int _end, Segment* _next, SegmentType _type)
	{
		start = _start;
		end = _end;
		next = _next;
		type = _type;
	}

	int start;
	int end;
	Segment* next;
	SegmentType type;

};
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

struct Jumper {
	Segment* segment;
	int statementIndex;
	bool jump = false;
};

class Kode : public Process {

public:
	Kode();
	Kode(Point _position, Point _size);

	void Draw(Point offset);

	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);

	void Run();
	void SetStatements(std::vector<std::string> _statements) { statements = _statements; }
	std::vector<ConsoleText> GetConsole() { return console; }

private:

	void DrawTextInput(Point offset);
	void DrawConsole(Point offset);

	void NewStatement();
	void SwitchStatement(int amount);
	void Input(std::string input);
	void Delete();
	void DeleteChar();
	void DeleteStatement();
	void MoveCursor(int toMove) { cursor += toMove; }

	void SetupSupportedSymbols();
	void SetupSupportedInstructions();

	void HandleStatement(std::string statement, int statementNumber);

	//instruction handling
	void HandleEmpty(int statementNumber);
	void HandleError(int statementNumber);
	void HandleNoInstruction(int statementNumber);
	void HandleOut(int statementNumber, std::vector<std::string> chunks);
	void HandleInt(int statementNumber, std::vector<std::string> chunks);
	void HandleBool(int statementNumber, std::vector<std::string> chunks);
	void HandleAssign(int statementNumber, std::vector<std::string> chunks);
	void HandleIf(int statementNumber, std::vector<std::string> chunks);
	void HandleWhile(int statementNumber, std::vector<std::string> chunks);

	void HandleEndIf(int statementNumber, std::vector<std::string> chunks);
	void HandleEndWhile(int statementNumber, std::vector<std::string> chunks);

	//variable edits
	bool ValidArithmeticOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);
	std::string ResolveArithmeticOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);
	bool ValidBooleanOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);
	std::string ResolveBooleanOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex = -1);

	//helpers
	Instruction CheckInstruction(std::vector<std::string> chunks);

	bool VariableExists(std::string toCheck);
	Variable* GetVariable(std::string toGet);
	void AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor);

	std::vector<std::string> StatementToChunk(std::string statement) { return Helper::Split(statement, " "); };
	VariableType ChunkType(std::string toCheck);
	std::string ResolveChunkValue(std::string chunk);
	std::string BoolToString(bool value) { return value ? "true" : "false"; }
	bool StringToBool(std::string value) { return value == "true"; }
	void SetupJump(Segment* _segmentToJumpTo, int _statementIndexToJumpTo);

	int Add(int a, int b) { return a + b; }
	int Minus(int a, int b) { return a - b; }
	int Multiply(int a, int b) { return a * b; }
	int Divide(int a, int b) { return a / b; }
	int Exponent(int a, int b) { return  std::pow(a, b); }

	int cursor;
	int statementFocus;

	std::vector<std::string> statements;
	std::vector<Variable*> variables;
	Segment* currentSegment;


	Jumper jumper;

	std::vector<std::string> arithmeticOperators;
	std::map<std::string, BoolOperator> booleanOperators;
	std::map<std::string, BoolComparator> booleanComparators;
	std::vector<std::string> notOperators;

	std::map<std::string, Instruction> supportedInstructions;

	std::vector<ConsoleText> console;
	int consoleHeight;
	bool debug;
	int fontSize;
};

