#include "kGraphics.h"
#include "Kode.h"
#include "Helper.h"


Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	SetupSupportedOpcodes();
	SetupSupportedSymbols();

	fontSize = 20;

	statements.push_back("out Hello world!");
	statements.push_back("out Hello second line! :)");

	statements.push_back("int x = 20");
	statements.push_back("int y = 30");
	statements.push_back("int z = y - x");
	statements.push_back("out z");

	statements.push_back("z = z / 0");
	statements.push_back("out z");

	/*statements.push_back("z = y + x");
	statements.push_back("out z");

	statements.push_back("z = y * x");
	statements.push_back("out z");

	statements.push_back("z = z + z");
	statements.push_back("out z");

	statements.push_back("z = z + 10");
	statements.push_back("out z");*/

	statementFocus = statements.size() - 1;

	consoleHeight = 100;
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

		Color toDraw = DARKGRAY;
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
	supportedSymbols.push_back("+");
	supportedSymbols.push_back("-");
	supportedSymbols.push_back("*");
	supportedSymbols.push_back("**");
	supportedSymbols.push_back("^");
	supportedSymbols.push_back("/");
}
void Kode::SetupSupportedOpcodes() {
	supportedOpCodes.push_back("out");
	supportedOpCodes.push_back("int");
}

//runs the program
void Kode::Run() {

	console.clear();
	variables.clear();

	//loops through each statement
	for (int i = 0; i < statements.size(); i++)
		HandleStatement(statements[i], i);
}

//handles the functionality of a statement
void Kode::HandleStatement(std::string statement, int statementNumber) {

	//splits the statement into the different chunks (defined by ' ')
	std::vector<std::string> chunks = Helper::Split(statement, " ");

	//gets what the first chunk was
	std::string foundOpcode = CheckOpcode(chunks);

	//empty statement
	if (foundOpcode == "empty")
		HandleOpEmpty(statementNumber);

	//unknown opcode
	if (foundOpcode == "error")
		HandleOpError(statementNumber);

	//empty opcode
	if (foundOpcode == "noOpcode")
		HandleOpNoOp(statementNumber);

	//out command
	if (foundOpcode == "out")
		HandleOpOut(statementNumber, chunks);

	//int command
	if (foundOpcode == "int")
		HandleOpInt(statementNumber, chunks);

	//assign command
	if (foundOpcode == "assign")
		HandleOpAssign(statementNumber, chunks);
}

//returns what opcode or alias was called
std::string Kode::CheckOpcode(std::vector<std::string> chunks) {

	//returns if the statement was empty
	if (chunks.size() == 1 && chunks[0] == "")
		return "empty";

	//returns if a valid opcode was found
	auto it = std::find(supportedOpCodes.begin(), supportedOpCodes.end(), chunks[0]);
	if (it != supportedOpCodes.end())
		return chunks[0];

	//returns if a variable identifier was found
	if (VariableExists(chunks[0]))
		return "assign";

	//returns if the first chunk was empty
	if (chunks[0] == "")
		return "noOpcode";

	//unknown error
	return "error";
}

void Kode::HandleOpEmpty(int statementNumber) {
	if (debug)
		AddToConsoleOutput(statementNumber, "Empty statement", RED);
	return;
}
void Kode::HandleOpError(int statementNumber) {
	if (debug)
		AddToConsoleOutput(statementNumber, "Unrecognized opcode", RED);
	return;
}
void Kode::HandleOpNoOp(int statementNumber) {
	if (debug)
		AddToConsoleOutput(statementNumber, "Empty opcode (Maybe you have a space at the start?)", RED);
	return;
}
void Kode::HandleOpOut(int statementNumber, std::vector<std::string> chunks) {

	//there is no chunks after the opcode
	if (chunks.size() < 2) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Nothing to output", RED);
		return;
	}

	//checks if the operand is an operation
	if (ValidOperation(chunks, 1)) {

		//gets the result of the operation
		std::string operationResult = ResolveOperation(statementNumber, chunks, 1);

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
void Kode::HandleOpInt(int statementNumber, std::vector<std::string> chunks) {

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

	//identifier is empty
	if (chunks[2] != "=") {
		if (debug)
			AddToConsoleOutput(statementNumber, "Missing the = symbol in declaration", RED);
		return;
	}

	//variable already existed
	if (VariableExists(chunks[1])) {
		AddToConsoleOutput(statementNumber, "Variable: " + chunks[1] + " already exists", RED);
		return;
	}

	//checks if the operand is an operation
	if (!ValidOperation(chunks, 3)) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Operation to assign is not valid", RED);
		return;
	}

	//gets the result of the operation
	std::string operationResult = ResolveOperation(statementNumber, chunks, 3);

	//declares and assigns values to the variable
	Variable* inter = new Variable();
	inter->identifier = chunks[1];
	inter->value = operationResult;
	inter->type = "integer";
	variables.push_back(inter);

	if (debug)
		AddToConsoleOutput(statementNumber, "Integer: " + inter->identifier + " with value: " + inter->value + " created", RED);
	return;
}
void Kode::HandleOpAssign(int statementNumber, std::vector<std::string> chunks) {

	//not enough chunks
	if (chunks.size() < 3) {
		if (debug)
			AddToConsoleOutput(statementNumber, "Need to have two operands for an int", RED);
		return;
	}

	//if the operand wasn't an eqauls
	if (chunks[1] != "=") {
		if (debug)
			AddToConsoleOutput(statementNumber, "Error trying to assign value without an '='", RED);
		return;
	}

	//gets the variable to assign to
	Variable* toAssign = GetVariable(chunks[0]);

	//assigning to an integer
	if (toAssign->type == "integer") {

		//checks if the operand is an operation
		if (!ValidOperation(chunks, 2)) {
			if (debug)
				AddToConsoleOutput(statementNumber, "Operation to assign is not valid", RED);
			return;
		}

		//gets the result of the operation
		std::string operationResult = ResolveOperation(statementNumber, chunks, 2);

		//assigns the value
		toAssign->value = operationResult;

		if (debug)
			AddToConsoleOutput(statementNumber, "Integer: " + toAssign->identifier + " given value: " + toAssign->value, RED);
		return;
	}
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

	Variable* toAssign = nullptr;

	//gets the variable being assigned
	for (int i = 0; i < variables.size(); i++)
		if (toGet == variables[i]->identifier)
			toAssign = variables[i];

	return toAssign;
}

//returns if the chunks from the startIndex onwards make a valid operation
bool Kode::ValidOperation(std::vector<std::string> chunks, int startIndex) {

	//checks if the number of chunks left are even
	if (chunks.size() - startIndex % 2 == 0)
		return false;

	//checks if the first chunk is not intable or a variable
	if (!(Helper::Intable(chunks[startIndex]) || VariableExists(chunks[startIndex])))
		return false;

	//loops through two chunks at a time until the end
	for (int i = startIndex + 1; i < chunks.size(); i += 2) {

		//checks if this wasn't supported symbol
		auto it = std::find(supportedSymbols.begin(), supportedSymbols.end(), chunks[i]);
		if (it == supportedSymbols.end())
			return false;

		if (!(Helper::Intable(chunks[i + 1]) || VariableExists(chunks[i + 1])))
			return false;
	}
	return true;
}

// resolves an operation
std::string Kode::ResolveOperation(int statementNumber, std::vector<std::string> chunks, int startIndex) {

	int result = 0;

	//saves either the variable value or direct value
	if (VariableExists(chunks[startIndex]))
		result = std::stoi(GetVariable(chunks[startIndex])->value);
	else
		result = std::stoi(chunks[startIndex]);

	//loops through two chunks at a time until the end
	for (int i = startIndex + 1; i < chunks.size(); i += 2) {

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

//adds a piece of text to the console lineup
void Kode::AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor) {

	ConsoleText ct;
	ct.linkedToStatement = statementNumber;
	ct.text = toAdd;
	ct.textColor = textColor;

	console.push_back(ct);
}


//To see instructions, go to the readme at https://github.com/KallumP/KallumOS/tree/readme#readme