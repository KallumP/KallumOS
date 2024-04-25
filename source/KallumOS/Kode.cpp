#include "kGraphics.h"
#include "Kode.h"
#include "Helper.h"
#include <algorithm>
#include <vector>

Kode::Kode() : Process("Kode") {
	currentSegment = nullptr;
	cursor = 0;
	statementFocus = 0;
	fontSize = 20;
	consoleHeight = 150;
	debug = false;
}

Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	SetupSupportedInstructions();
	SetupSupportedSymbols();

	fontSize = 20;

	//default statements
	statements.push_back("out Hello world!");
	statements.push_back("out Hello second line! 0:)");

	//kode test statements are found at "kodeTests.txt"

	statementFocus = statements.size() - 1;

	consoleHeight = 150;
	AddToConsoleOutput(0, "Press F5 to compile your text", BLUE);
	AddToConsoleOutput(1, "Press F3 to on debug outputs", BLUE);

	debug = false;
}

void Kode::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		DrawTextInput(offset);
		DrawConsole(offset);
	}
}
void Kode::DrawTextInput(Point offset) {

	int padding = 10;

	//how many of the biggest char can fit in the box
	int charsPerLine = (size.GetX() - padding * 2) / MeasureText("X", fontSize);

	//loops through each statement
	int lineCount = 0;
	for (int i = 0; i < statements.size(); i++) {

		//sets up the statement with the line number
		std::string text = std::to_string(i) + ". " + statements[i];

		Color toDraw = GRAY;
		if (i == statementFocus)
			toDraw = BLACK;

		//if there wasn't enough characters to fill a line
		if (text.size() < charsPerLine) {

			kGraphics::DrawString(text, padding + offset.GetX(), offset.GetY() + padding + (GetNextLineY(lineCount)), fontSize, toDraw);
			lineCount++;

		} else {

			//gets the number of lines that need to be drawn for this statemenet
			int linesToDraw = std::ceil(text.size() / (float)charsPerLine);

			//loops through each line
			for (int j = 0; j < linesToDraw; j++) {

				std::string line = text.substr(j * charsPerLine, charsPerLine);
				kGraphics::DrawString(line, padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(lineCount), fontSize, toDraw);
				lineCount++;
			}
		}
	}
}
void Kode::DrawConsole(Point offset) {

	int padding = 10;

	offset.SetY(offset.GetY() + size.GetY() - consoleHeight);
	kGraphics::FillRect(offset.GetX(), offset.GetY(), size.GetX(), consoleHeight, BLACK);

	//how many of the biggest char can fit in the box
	int charsPerLine = (size.GetX() - padding * 2) / MeasureText("X", fontSize);

	int lineCount = 0;
	for (int i = 0; i < console.size(); i++) {

		//gets the string to output
		std::string text = std::to_string(console[i].linkedToStatement) + ". " + console[i].text;

		if (text.size() < charsPerLine) {

			kGraphics::DrawString(text, padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(lineCount), fontSize, console[i].textColor);
			lineCount++;

		} else {

			//gets the number of lines that need to be drawn for this statemenet
			int linesToDraw = std::ceil(text.size() / (float)charsPerLine);

			//loops through each line
			for (int j = 0; j < linesToDraw; j++) {

				std::string line = text.substr(j * charsPerLine, charsPerLine);
				kGraphics::DrawString(line, padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(lineCount), fontSize, console[i].textColor);
				lineCount++;
			}
		}
	}
}

void Kode::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == KEY_BACKSPACE) {
		Delete();
		return;
	} else if (e->GetKeyCode() == KEY_LEFT) {
		//MoveCursor(-1);
		return;
	} else if (e->GetKeyCode() == KEY_RIGHT) {
		//MoveCursor(1);
		return;
	} else if (e->GetKeyCode() == KEY_F5) {
		Run();
		return;
	} else if (e->GetKeyCode() == KEY_F3) {
		debug = !debug;
		return;
	} else if (e->GetKeyCode() == KEY_ENTER) {
		NewStatement();
		return;
	} else if (e->GetKeyCode() == KEY_UP) {
		SwitchStatement(-1);
		return;
	} else if (e->GetKeyCode() == KEY_DOWN) {
		SwitchStatement(1);
		return;
	}

	if (e->GetKeyContent().length() != 0)
		Input(e->GetKeyContent());
}

void Kode::OnMousePress(MousePress* e) {

	if (display) {

		SuperMousePress(Helper::NormaliseMousePos(e->GetMousePosition(), position));

		int checkOffset;

		//saves the height of the mouse
		Point normalisedMouse = Helper::NormaliseMousePos(e->GetMousePosition(), position);

		//move cursor to something near the text
	}
}

//adds a new statement after the currently focused statement
void Kode::NewStatement() {

	statements.insert(statements.begin() + statementFocus + 1, "");
	statementFocus++;
}

void Kode::SwitchStatement(int amount) {

	statementFocus += amount;

	statementFocus = statementFocus < 0 ? 0 : statementFocus;
	statementFocus = statementFocus > statements.size() - 1 ? statements.size() - 1 : statementFocus;
}

//input handling
void Kode::Input(std::string input) {
	statements[statementFocus].append(input);
}

//delete handling
void Kode::Delete() {

	//if there was text in this statement
	if (statements[statementFocus].length() != 0)
		DeleteChar();

	//if there was no text in this statement
	else
		DeleteStatement();
}

//deletes a char or the statement if no chars
void Kode::DeleteChar() {

	statements[statementFocus].pop_back();
}

//deletes the current statement
void Kode::DeleteStatement() {

	if (statements.size() > 1) { //if this isnt the last statement

		//deletes this statement
		statements.erase(statements.begin() + statementFocus);

		//updates what statement to focus on
		statementFocus--;

		//stops the focus being below 0
		statementFocus = statementFocus < 0 ? 0 : statementFocus;
	}
}

void Kode::SetupSupportedSymbols() {
	arithmeticOperators.push_back("+");
	arithmeticOperators.push_back("-");
	arithmeticOperators.push_back("*");
	arithmeticOperators.push_back("/");
	arithmeticOperators.push_back("^");
	arithmeticOperators.push_back("**");

	booleanOperators["&&"] = BoolOperator::And;
	booleanOperators["||"] = BoolOperator::Or;
	booleanOperators["^^"] = BoolOperator::Or;

	notOperators.push_back("!");
	notOperators.push_back("¬");
	notOperators.push_back("`");

	booleanComparators["=="] = BoolComparator::Equal;
	booleanComparators["!="] = BoolComparator::NotEqual;
	booleanComparators["<"] = BoolComparator::Less;
	booleanComparators["<="] = BoolComparator::LessEqual;
	booleanComparators[">"] = BoolComparator::More;
	booleanComparators[">="] = BoolComparator::MoreEqual;

}
void Kode::SetupSupportedInstructions() {
	supportedInstructions["out"] = Instruction::Out;
	supportedInstructions["int"] = Instruction::Int;
	supportedInstructions["bool"] = Instruction::Bool;
	supportedInstructions["if"] = Instruction::If;
	supportedInstructions["endif"] = Instruction::EndIf;
}

//runs the program
void Kode::Run() {

	console.clear();
	variables.clear();

	jumper = Jumper();

	currentSegment = new Segment(0, statements.size() - 1, nullptr); //the whole program as one segment

	//keeps going until all segments have been executed
	while (currentSegment != nullptr) {

		//loops through each statement in this segment
		for (int i = currentSegment->start; i <= currentSegment->end; i++) {

			HandleStatement(statements[i], i);

			//jumps to a statement if necessary
			if (jumper.jump) {

				currentSegment = jumper.segment;
				i = jumper.statementIndex;
				jumper.jump = false;
			}
		}

		//TODO: unallocate all segments as they get used up

		//moves onto the next segment
		currentSegment = currentSegment->next; 
	}
}

void Kode::SetupJump(Segment* _segmentToJumpTo, int _statementIndexToJumpTo) {

	jumper.segment = _segmentToJumpTo;
	jumper.statementIndex = _statementIndexToJumpTo;
	jumper.jump = true;
}

//handles the functionality of a statement
void Kode::HandleStatement(std::string statement, int statementIndex) {

	//splits the statement into the different chunks (defined by ' ')
	std::vector<std::string> chunks = StatementToChunk(statement);

	//gets what the first chunk was
	Instruction foundInstruction = CheckInstruction(chunks);

	switch (foundInstruction) {

		case Instruction::Empty: //empty statement
			HandleEmpty(statementIndex);
			break;

		case Instruction::Error: //unknown instruction
			HandleError(statementIndex);
			break;

		case Instruction::NoInstruction: //empty instruction
			HandleNoInstruction(statementIndex);
			break;

		case Instruction::Out: //out command
			HandleOut(statementIndex, chunks);
			break;

		case Instruction::Int: //int command
			HandleInt(statementIndex, chunks);
			break;

		case Instruction::Bool: //bool command
			HandleBool(statementIndex, chunks);
			break;

		case Instruction::Assign: //assign command
			HandleAssign(statementIndex, chunks);
			break;

		case Instruction::If: //if statment instruction
			HandleIf(statementIndex, chunks);
			break;
	}
}

//returns what instruction or alias was called
Instruction Kode::CheckInstruction(std::vector<std::string> chunks) {

	//returns if the statement was empty
	if (chunks.size() == 1 && chunks[0] == "")
		return Instruction::Empty;

	//returns if a valid manual instruction was found
	if (supportedInstructions.find(chunks[0]) != supportedInstructions.end())
		return supportedInstructions[chunks[0]];

	//returns if a variable identifier was found
	if (VariableExists(chunks[0]))
		return Instruction::Assign;

	//returns if the first chunk was empty
	if (chunks[0] == "")
		return Instruction::NoInstruction;

	//unknown error
	return Instruction::Error;
}


void Kode::HandleEmpty(int statementNumber) {
	if (debug)
		AddToConsoleOutput(statementNumber, "Empty statement", RED);
	return;
}
void Kode::HandleError(int statementNumber) {
	if (debug)
		AddToConsoleOutput(statementNumber, "Unrecognized instruction", RED);
	return;
}
void Kode::HandleNoInstruction(int statementNumber) {
	if (debug)
		AddToConsoleOutput(statementNumber, "No instruction (Maybe you have a space at the start?)", RED);
	return;
}
void Kode::HandleOut(int statementNumber, std::vector<std::string> chunks) {

	//there is no chunks after the instruction
	if (chunks.size() < 2) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Nothing to output", RED);
		return;
	}

	if (ValidArithmeticOperation(statementNumber, chunks, 1)) { //checks if the operation to output is arithmetic

		std::string operationResult = ResolveArithmeticOperation(statementNumber, chunks, 1);
		AddToConsoleOutput(statementNumber, operationResult, WHITE);
		return;

	} else if (ValidBooleanOperation(statementNumber, chunks, 1)) { //checks if the operation to output is boolean

		std::string operationResult = ResolveBooleanOperation(statementNumber, chunks, 1);
		AddToConsoleOutput(statementNumber, operationResult, WHITE);
		return;

	}

	//loops through all the chunks and gets the whole output
	std::string operand = "";
	for (int j = 1; j < chunks.size(); j++)
		operand += chunks[j] + " ";

	AddToConsoleOutput(statementNumber, operand, WHITE);
	return;
}
void Kode::HandleInt(int statementNumber, std::vector<std::string> chunks) {

	//not enough chunks
	if (chunks.size() < 4) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Not enough chunks for this statement, should be atleast 4", RED);
		return;
	}

	//identifier is empty
	if (chunks[1] == "") {
		if (debug)
			AddToConsoleOutput(statementNumber, "Cannot have empty variable identifier in declaration", RED);
		return;
	}

	//identifier is missing
	if (chunks[2] != "=") {
		if (debug)
			AddToConsoleOutput(statementNumber, "Missing the = symbol in declaration", RED);
		return;
	}

	//variable already existed
	if (VariableExists(chunks[1])) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Variable: " + chunks[1] + " already exists", RED);
		return;
	}

	//checks if the chunks are a valid operation
	if (!ValidArithmeticOperation(statementNumber, chunks, 3)) {
		AddToConsoleOutput(statementNumber, "Error: " + chunks[1] + " variable was not set", RED);
		return;
	}

	//gets the result of the operation
	std::string operationResult = ResolveArithmeticOperation(statementNumber, chunks, 3);

	//declares and assigns values to the variable
	Variable* inter = new Variable();
	inter->identifier = chunks[1];
	inter->value = operationResult;
	inter->type = VariableType::Int;
	variables.push_back(inter);

	if (debug)
		AddToConsoleOutput(statementNumber, "Integer: " + inter->identifier + " with value: " + inter->value + " created", RED);
	return;
}
void Kode::HandleBool(int statementNumber, std::vector<std::string> chunks) {

	//not enough chunks
	if (chunks.size() < 4) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Not enough chunks for this statement, should be atleast 4", RED);
		return;
	}

	//identifier is empty
	if (chunks[1] == "") {
		if (debug)
			AddToConsoleOutput(statementNumber, "Cannot have empty variable identifier in declaration", RED);
		return;
	}

	//identifier is missing
	if (chunks[2] != "=") {
		if (debug)
			AddToConsoleOutput(statementNumber, "Missing the = symbol in declaration", RED);
		return;
	}

	//variable already existed
	if (VariableExists(chunks[1])) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Variable: " + chunks[1] + " already exists", RED);
		return;
	}

	//not a valid boolean operation
	if (!ValidBooleanOperation(statementNumber, chunks, 3)) {
		AddToConsoleOutput(statementNumber, "Error: " + chunks[1] + " variable was not set", RED);
		return;
	}

	//resolve the boolean operation
	std::string resolved = ResolveBooleanOperation(statementNumber, chunks, 3);


	//declares and assigns values to the variable
	Variable* boolean = new Variable();
	boolean->identifier = chunks[1];
	boolean->value = resolved;
	boolean->type = VariableType::Bool;
	variables.push_back(boolean);

	if (debug)
		AddToConsoleOutput(statementNumber, "Boolean: " + boolean->identifier + " with value: " + boolean->value + " created", RED);
	return;

}
void Kode::HandleAssign(int statementNumber, std::vector<std::string> chunks) {

	//not enough chunks
	if (chunks.size() < 3) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Need to have two chunks for an assign, need to have three", RED);
		return;
	}

	//if the second chunk wasn't an eqauls
	if (chunks[1] != "=") {
		if (debug)
			AddToConsoleOutput(statementNumber, "Error trying to assign value without an '='", RED);
		return;
	}

	//gets the variable to assign to
	Variable* toAssign = GetVariable(chunks[0]);
	std::string operationResult;

	switch (toAssign->type) {

		case VariableType::Int: //assigning to an integer

			//checks if the operand is an operation
			if (!ValidArithmeticOperation(statementNumber, chunks, 2)) {
				if (debug)
					AddToConsoleOutput(statementNumber, "Operation to assign is not valid", RED);
				return;
			}

			//gets the result of the operation
			operationResult = ResolveArithmeticOperation(statementNumber, chunks, 2);

			//assigns the value
			toAssign->value = operationResult;

			if (debug)
				AddToConsoleOutput(statementNumber, "Integer: " + toAssign->identifier + " given value: " + toAssign->value, RED);
			break;

		case VariableType::Bool: //assigning to a bool

			if (!ValidBooleanOperation(statementNumber, chunks, 2)) {
				if (debug)
					AddToConsoleOutput(statementNumber, "Operation to assign is not valid", RED);
				return;
			}

			//gets the result of the operation
			operationResult = ResolveBooleanOperation(statementNumber, chunks, 2);

			//assigns the value
			toAssign->value = operationResult;

			if (debug)
				AddToConsoleOutput(statementNumber, "Boolean: " + toAssign->identifier + " given value: " + toAssign->value, RED);
			break;
	}
}
void Kode::HandleIf(int statementNumber, std::vector<std::string> chunks) {

	//not enough chunks (needs the if and atleast a single boolean value)
	if (chunks.size() < 2) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Need to have two chunks for an if, needs to have 2", RED);
		return;
	}

	//handles if the if condition was bad
	if (!ValidBooleanOperation(statementNumber, chunks, 1, chunks.size() - 1)) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Invalid boolean condition for if statement", RED);
		return;
	}

	//find corresponding endif instruction
	int endIfIndex = -1;
	int foundIfs = 1;
	for (int i = statementNumber + 1; i < currentSegment->end; i++) {

		std::vector<std::string> toCheck = StatementToChunk(statements[i]);
		Instruction instruction = CheckInstruction(toCheck);

		if (instruction == Instruction::If) {

			foundIfs++; //keeps track of this if instruction
		
		} else if (instruction == Instruction::EndIf) {

			foundIfs--; //notes that an endif instruction was found

			if (foundIfs == 0) { // this endif doesn't belong to an inner if block

				endIfIndex = i;
				break;
			}
		}
	}

	// no corresponding endif found
	if (endIfIndex == -1) {
		AddToConsoleOutput(statementNumber, "No endif instruction found to complete this if statement", RED);
		return;
	}

	int ifStartIndex = statementNumber + 1;

	//create exit segment
	Segment* exitSegment = new Segment(endIfIndex + 1, currentSegment->end, currentSegment->next);

	//create if segment
	Segment* ifSeg = new Segment(ifStartIndex, endIfIndex, exitSegment);

	//restructure outer segment
	currentSegment->end = statementNumber;
	currentSegment->next = ifSeg;


	//if condition was false
	bool conditionResolve = StringToBool(ResolveBooleanOperation(statementNumber, chunks, 1, chunks.size() - 1));
	if (!conditionResolve)

		//sets up a jump to the end of the if statement
		SetupJump(ifSeg, ifSeg->end);


	//if condition was true no action is needed, because the previous segment will end and the if segment will start automatically
	//consider putting a jump once the jumper is changed to jump to the start of the next segment

	if (debug) {
		std::string message = "If statement [" + std::to_string(ifStartIndex) + " - " + std::to_string(endIfIndex) + "] " + BoolToString(conditionResolve);
		AddToConsoleOutput(statementNumber, message, BLUE);
		return;
	}

	//todo

	//nested if statement
	//problem is, when inserting segments, they get added to the end
	//this means that the order of segments will be wrong when there are nested segments

	//this can be fixed by inserting the segment into the right place of the list
	//and using a function to get the index of a segment
	
	//possibly move towards a list based segment storage to stop pointers becoming stale when inserting into the vector


	//todo 
	//if a jump is needed, jump before handling the next statement, not after handling the current statement 
	//jump should happen at the start of the inner for loop of run
	//this lets the jumper jump to the start of the next segment, rather than the end of the current segment

	//the segments should be stored in a linked list
	//the outer run loop should be a list traversal until the end of the list is reached
}

//returns if the chunks from the startIndex onwards make a valid arithmetic operation
bool Kode::ValidArithmeticOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex) {

	if (endIndex == -1)
		endIndex = chunks.size() - 1;

	//checks if the number of chunks left are even
	if ((endIndex - startIndex) % 2 == 1)
		return false;

	if (VariableExists(chunks[startIndex]))
		if (GetVariable(chunks[startIndex])->type != VariableType::Int)
			return false;

	//checks if the first chunk is not intable or a variable
	if (!(Helper::Intable(chunks[startIndex]) || VariableExists(chunks[startIndex])))
		return false;

	//loops through two chunks at a time until the end
	for (int i = startIndex + 1; i <= endIndex; i += 2) {

		//checks if this wasn't supported symbol
		if (std::find(arithmeticOperators.begin(), arithmeticOperators.end(), chunks[i]) == arithmeticOperators.end())
			return false;

		if (VariableExists(chunks[i + 1]))
			if (GetVariable(chunks[i + 1])->type != VariableType::Int)
				return false;

		if (!(Helper::Intable(chunks[i + 1]) || VariableExists(chunks[i + 1])))
			return false;
	}
	return true;
}

//returns the resolution of an arithmetic operation
std::string Kode::ResolveArithmeticOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex) {

	if (endIndex == -1)
		endIndex = chunks.size() - 1;

	int result = 0;

	//saves either the variable value or direct value
	if (VariableExists(chunks[startIndex]))
		result = std::stoi(GetVariable(chunks[startIndex])->value);
	else
		result = std::stoi(chunks[startIndex]);

	//loops through two chunks at a time until the end
	for (int i = startIndex + 1; i <= endIndex; i += 2) {

		int toWorkWith;

		//saves either the variable value or direct value
		if (VariableExists(chunks[i + 1]))
			toWorkWith = std::stoi(GetVariable(chunks[i + 1])->value);
		else
			toWorkWith = std::stoi(chunks[i + 1]);

		//handles the two values using the used operation
		if (chunks[i] == "+")
			result = Add(result, toWorkWith);
		else if (chunks[i] == "-")
			result = Minus(result, toWorkWith);
		else if (chunks[i] == "*")
			result = Multiply(result, toWorkWith);
		else if (chunks[i] == "**" || chunks[i] == "^")
			result = Exponent(result, toWorkWith);
		else if (chunks[i] == "/") {
			if (toWorkWith == 0) {
				AddToConsoleOutput(statementNumber, "Tried to divide by zero. Division operation skipped", RED);
				continue;
			}
			result = Divide(result, toWorkWith);
		}
	}

	return std::to_string(result);
}

//returns if the chunks from the startIndex onward make a valid boolean operation
bool Kode::ValidBooleanOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex) {

	if (endIndex == -1)
		endIndex = chunks.size() - 1;

	int numberOfCheckDelimeters = 0;
	int delimeterIndex = 0;

	//loops through the chunks and checks how many comparators there were
	for (int i = startIndex; i <= endIndex; i++) {
		if (booleanComparators.find(chunks[i]) != booleanComparators.end()) {
			numberOfCheckDelimeters++;
			delimeterIndex = i;
		}
	}

	//checks if there were too many == found
	if (numberOfCheckDelimeters > 1) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Too many '==' entered", RED);
		return false;
	}

	//checks if either side of the == has the same variable type
	if (numberOfCheckDelimeters == 1) {

		//if there wasnt enough chunks (needs to be atleast 3)
		if (endIndex - startIndex < 2) {
			if (debug)
				AddToConsoleOutput(statementNumber, "Not enough chunks", RED);
			return false;
		}

		//if the delimeter was the first or last chunk
		if (delimeterIndex == startIndex || delimeterIndex == endIndex) {
			if (debug)
				AddToConsoleOutput(statementNumber, "The lSide or rSide was missing for the comparison", RED);
			return false;
		}

		int checkIndex = startIndex;
		std::string chunk = chunks[checkIndex];
		VariableType type = VariableExists(chunk) ? GetVariable(chunk)->type : ChunkType(chunk);

		bool lSide = false;
		bool rSide = false;

		//get the first chunk's type and store it in "type"
		if (type == VariableType::Int) {

			lSide = ValidArithmeticOperation(statementNumber, chunks, startIndex, delimeterIndex - 1);
			rSide = ValidArithmeticOperation(statementNumber, chunks, delimeterIndex + 1, endIndex);

		} else if (type == VariableType::Bool) {

			lSide = ValidBooleanOperation(statementNumber, chunks, startIndex, delimeterIndex - 1);
			rSide = ValidBooleanOperation(statementNumber, chunks, delimeterIndex + 1, endIndex);

		} else if (type == VariableType::String) {

			if (debug)
				AddToConsoleOutput(statementNumber, "String comparison not supported, maybe you spelt a variable name wrong?", RED);
			return false;

		}

		//both sides were the same variable type
		return lSide && rSide;
	}

	//checks for if no == were found
	int checkIndex = startIndex;
	bool lookingForValue = true;

	while (checkIndex <= endIndex) {

		std::string currentChunk = chunks[checkIndex];

		if (lookingForValue) {

			//if the current chunk is a "not" symbol
			if (std::find(notOperators.begin(), notOperators.end(), currentChunk) != notOperators.end()) {

				//if this was the last chunk, this is a bad structure
				if (checkIndex == endIndex)
					return false;

				lookingForValue = !lookingForValue; //pre flips this so that it reverts back when flipped at the end of the loop

			} else {

				//if the current chunk is not boolean, this is a bad structure
				if (ChunkType(currentChunk) != VariableType::Bool)
					return false;
			}

		} else {

			//if the value was not found in the boolean operator list, this is a bad structure
			if (booleanOperators.find(currentChunk) == booleanOperators.end())
				return false;

			//if this was the last chunk, this is a bad structure
			if (checkIndex == endIndex)
				return false;
		}

		checkIndex++;//increase the check index
		lookingForValue = !lookingForValue;//next value should be a boolean operator
	}

	return true;
}

//returns the resolution of a boolean operation
std::string Kode::ResolveBooleanOperation(int statementNumber, std::vector<std::string> chunks, int startIndex, int endIndex) {

	if (endIndex == -1)
		endIndex = chunks.size() - 1;

	int numberOfCheckDelimeters = 0;
	int delimeterIndex = 0;
	BoolComparator comparator;

	//loops through the chunks and checks how many comparators there were
	for (int i = startIndex; i <= endIndex; i++) {
		if (booleanComparators.find(chunks[i]) != booleanComparators.end()) {
			numberOfCheckDelimeters++;
			delimeterIndex = i;
			comparator = booleanComparators[chunks[i]];
		}
	}

	//checks if either side of the == has the same variable type
	if (numberOfCheckDelimeters == 1) {

		int checkIndex = startIndex;
		std::string chunk = chunks[checkIndex];
		VariableType type = VariableExists(chunk) ? GetVariable(chunk)->type : ChunkType(chunk);
		std::string lSide;
		std::string rSide;


		if (type == VariableType::Int) {

			lSide = ResolveArithmeticOperation(statementNumber, chunks, startIndex, delimeterIndex - 1);
			rSide = ResolveArithmeticOperation(statementNumber, chunks, delimeterIndex + 1, endIndex);

		} else if (type == VariableType::Bool) {

			lSide = ResolveBooleanOperation(statementNumber, chunks, startIndex, delimeterIndex - 1);
			rSide = ResolveBooleanOperation(statementNumber, chunks, delimeterIndex + 1, endIndex);

		}

		//does the evaluation of the two side values
		switch (comparator) {
			case BoolComparator::Equal:
				return BoolToString(lSide == rSide);
			case BoolComparator::NotEqual:
				return BoolToString(lSide != rSide);
			case BoolComparator::Less:
				return BoolToString(lSide < rSide);
			case BoolComparator::LessEqual:
				return BoolToString(lSide <= rSide);
			case BoolComparator::More:
				return BoolToString(lSide > rSide);
			case BoolComparator::MoreEqual:
				return BoolToString(lSide >= rSide);
		}
	}

	//resolve pure boolean algebra
	bool resolvedValue = false;
	int currentIndex = startIndex;
	BoolOperator nextOperator = BoolOperator::Null;

	//loops through the chunks for this operation
	while (currentIndex <= endIndex) {

		bool currentValue;

		//gets the current chunk value
		if (std::find(notOperators.begin(), notOperators.end(), chunks[currentIndex]) != notOperators.end())
			currentValue = !StringToBool(ResolveChunkValue(chunks[(++currentIndex)++]));//gets the negated value of the next chunk and then increments
		else
			currentValue = StringToBool(ResolveChunkValue(chunks[currentIndex++]));//gets the negated value of the current chunk and then increments

		//handle combining the current value with the current resolved value
		switch (nextOperator) {

			case BoolOperator::Null:
				resolvedValue = currentValue;
				break;

			case BoolOperator::And:
				resolvedValue = resolvedValue && currentValue;
				break;

			case BoolOperator::Or:
				resolvedValue = resolvedValue || currentValue;
				break;
		}

		//ends the loop if there is nothing left
		if (currentIndex > endIndex)
			break;

		//get what the next operator should be
		nextOperator = booleanOperators[chunks[currentIndex++]];
	}

	return BoolToString(resolvedValue);
}

//returns if a variable exists
bool Kode::VariableExists(std::string toCheck) {

	//returns if a variable identifier was found
	for (int i = 0; i < variables.size(); i++)
		if (toCheck == variables[i]->identifier)
			return true;
	return false;
}

//returns the pointer to the passed variable identifier
Variable* Kode::GetVariable(std::string toGet) {

	Variable* v = nullptr;

	//gets the variable being assigned
	for (int i = 0; i < variables.size(); i++)
		if (toGet == variables[i]->identifier)
			v = variables[i];

	return v;
}

//adds a piece of text to the console lineup
void Kode::AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor) {

	ConsoleText ct;
	ct.linkedToStatement = statementNumber;
	ct.text = toAdd;
	ct.textColor = textColor;

	console.push_back(ct);
}

//returns what type of variable a string could be
VariableType Kode::ChunkType(std::string toCheck) {

	//if it was a variable return it's type
	if (VariableExists(toCheck))
		return GetVariable(toCheck)->type;

	//if it is not a variable, return the potential type
	else {

		if (Helper::Intable(toCheck))
			return VariableType::Int;

		if (toCheck == "true" || toCheck == "false")
			return VariableType::Bool;

		return VariableType::String;
	}
}

//returns the resolved value of a chunk
std::string Kode::ResolveChunkValue(std::string chunk) {

	//if it was a variable return its value
	if (VariableExists(chunk))
		return GetVariable(chunk)->value;

	//if it is not a variable, return the string value
	else
		return chunk;
}

//To see instructions, go to the readme at https://github.com/KallumP/KallumOS/tree/readme#readme