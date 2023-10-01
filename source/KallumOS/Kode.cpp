#include "kGraphics.h"
#include "Kode.h"
#include "Helper.h"


Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	SetupSupportedOpcodes();
	SetupSupportedSymbols();

	fontSize = 20;
	text = "out Hello world!;out Hello second line!:);";
	//text = "int x = 20;int y = 30;";
	//text += "int z = y - x;out z;";
	//text += "z = y + x;out z;";
	//text += "z = y * x;out z;";
	//text += "z = z + z;out z;";
	//text += "z = z + 10;out z;";

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

	//gets each statement in a vector
	std::vector<std::string> statements = Split(text, ";");

	//loops through each statement
	int lineCount = 0;
	for (int i = 0; i < statements.size(); i++) {

		//gets the string to output
		std::string text = "";
		text += std::to_string(lineCount) + ". ";
		text += statements[i];
		if (i != statements.size() - 1)
			text += ";";


		//if there wasn't enough characters to fill a line
		if (text.size() < charsPerLine) {

			kGraphics::DrawString(text, padding + offset.GetX(), offset.GetY() + padding + (GetNextLineY(lineCount)), fontSize, BLACK);
			lineCount++;

		} else {

			//gets the number of lines that need to be drawn for this statemenet
			int linesToDraw = std::ceil(text.size() / (float)charsPerLine);

			//loops through each line
			for (int i = 0; i < linesToDraw; i++) {

				std::string line;
				line = text.substr(i * charsPerLine, charsPerLine);

				kGraphics::DrawString(line, padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(lineCount), fontSize, BLACK);
				lineCount++;
			}
		}
	}
}
void Kode::DrawConsole(Point offset) {

	int padding = 10;

	offset.SetY(offset.GetY() + size.GetY() - consoleHeight);
	kGraphics::FillRect(offset.GetX(), offset.GetY(), size.GetX(), consoleHeight, BLACK);


	for (int i = 0; i < console.size(); i++) {

		//gets the string to output
		std::string text = "";
		text += std::to_string(console[i].linkedToStatement) + ". ";
		text += console[i].text;

		kGraphics::DrawString(text, padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(i), fontSize, console[i].textColor);
	}
}


void Kode::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == KEY_BACKSPACE) {
		DeleteChar();
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

void Kode::Input(std::string input) {
	text.append(input);
}

void Kode::DeleteChar() {

	if (text.length() != 0) {

		text.pop_back();

	} else {

	}
}

std::vector<std::string> Kode::Split(std::string toSplit, std::string delimiter) {


	std::vector<std::string> toReturn;
	size_t pos = 0;

	while ((pos = toSplit.find(delimiter)) != std::string::npos) {
		toReturn.push_back(toSplit.substr(0, pos));
		toSplit.erase(0, pos + delimiter.length());
	}
	toReturn.push_back(toSplit);

	return toReturn;
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

void Kode::Run() {

	console.clear();
	variables.clear();

	//splits the text into statements (defined by ';')
	std::vector<std::string> statements = Split(text, ";");

	//loops through each statement
	for (int i = 0; i < statements.size(); i++) {

		//checks if this was an empty statement
		if (statements[i].size() == 0) {
			if (debug)
				AddToConsoleOutput(i, "Empty statement", RED);
			continue;
		}

		//splits the statement into the different chunks (defined by ' ')
		std::vector<std::string> chunks = Split(statements[i], " ");

		//gets what the first chunk was
		std::string foundOpcode = CheckOpcode(chunks);

		//unknown opcode
		if (foundOpcode == "error") {
			if (debug)
				AddToConsoleOutput(i, "Unrecognized opcode", RED);
			continue;
		}

		//empty opcode
		if (foundOpcode == "empty") {
			if (debug)
				AddToConsoleOutput(i, "Empty opcode (Maybe you have a space at the start?)", RED);
			continue;
		}

		//out command
		if (foundOpcode == "out") {

			//there is no chunks after the opcode
			if (chunks.size() < 2) {
				if (debug)
					AddToConsoleOutput(i, "Nothing to output", RED);
				continue;
			}

			//checks if the operand is a function
			if (ValidFunction(chunks, 1)) {

				//gets the result of the function
				std::string functionResult = HandleFunction(i, chunks, 1);

				AddToConsoleOutput(i, functionResult, WHITE);
				continue;
			}

			//loops through all the chunks and gets the whole output
			std::string operand = "";
			for (int j = 1; j < chunks.size(); j++)
				operand += chunks[j] + " ";

			AddToConsoleOutput(i, operand, WHITE);
			continue;
		}

		//int command
		if (foundOpcode == "int") {

			//not enough chunks
			if (chunks.size() < 4) {
				if (debug)
					AddToConsoleOutput(i, "Not enough chunks for this statement, should be atleast 4", RED);
				continue;
			}

			//identifier is empty
			if (chunks[1] == "") {
				if (debug)
					AddToConsoleOutput(i, "Cannot have empty variable identifier in declaration", RED);
				continue;
			}

			//identifier is empty
			if (chunks[2] != "=") {
				if (debug)
					AddToConsoleOutput(i, "Missing the = symbol in declaration", RED);
				continue;
			}

			//variable already existed
			if (VariableExists(chunks[1])) {
				AddToConsoleOutput(i, "Variable: " + chunks[1] + " already exists", RED);
				continue;
			}

			//checks if the operand is a function
			if (!ValidFunction(chunks, 3)) {
				if (debug)
					AddToConsoleOutput(i, "Function to assign is not valid", RED);
				continue;
			}

			//gets the result of the function
			std::string functionResult = HandleFunction(i, chunks, 3);

			//declares and assigns values to the variable
			Variable* inter = new Variable();
			inter->identifier = chunks[1];
			inter->value = functionResult;
			inter->type = "integer";
			variables.push_back(inter);

			if (debug)
				AddToConsoleOutput(i, "Integer: " + inter->identifier + " with value: " + inter->value + " created", RED);
			continue;
		}

		//assign command
		if (foundOpcode == "assign") {

			//not enough chunks
			if (chunks.size() < 3) {
				if (debug)
					AddToConsoleOutput(i, "Need to have two operands for an int", RED);
				continue;
			}

			//if the operand wasn't an eqauls
			if (chunks[1] != "=") {
				if (debug)
					AddToConsoleOutput(i, "Error trying to assign value without an '='", RED);
				continue;
			}

			//gets the variable to assign to
			Variable* toAssign = GetVariable(chunks[0]);

			//assigning to an integer
			if (toAssign->type == "integer") {

				//checks if the operand is a function
				if (!ValidFunction(chunks, 2)) {
					if (debug)
						AddToConsoleOutput(i, "Function to assign is not valid", RED);
					continue;
				}

				//gets the result of the function
				std::string functionResult = HandleFunction(i, chunks, 2);

				//assigns the value
				toAssign->value = functionResult;

				if (debug)
					AddToConsoleOutput(i, "Integer: " + toAssign->identifier + " given value: " + toAssign->value, RED);
				continue;
			}
		}
	}
}

//returns what opcode or alias was called
std::string Kode::CheckOpcode(std::vector<std::string> chunks) {

	//returns if a valid opcode was found
	auto it = std::find(supportedOpCodes.begin(), supportedOpCodes.end(), chunks[0]);
	if (it != supportedOpCodes.end())
		return chunks[0];

	//returns if a variable identifier was found
	if (VariableExists(chunks[0]))
		return "assign";

	if (chunks[0] == "")
		return "empty";

	return "error";
}

//adds a piece of text to the console lineup
void Kode::AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor) {

	ConsoleText ct;
	ct.linkedToStatement = statementNumber;
	ct.text = toAdd;
	ct.textColor = textColor;

	console.push_back(ct);
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

//returns if a string can be tuend into an int
bool Kode::Intable(std::string toCheck) {

	////checks if all the chars were numbers
	//for (char c : toCheck)
	//	if (!isdigit(c))
	//		return false;

	//tries to convert the value into an int
	bool intable = true;
	try {
		std::stoi(toCheck);
	} catch (const std::invalid_argument& e) {
		intable = false;
	}

	return intable;
}

//returns if the chunks from the startIndex onwards make a valid function
bool Kode::ValidFunction(std::vector<std::string> chunks, int startIndex) {

	//checks if the number of chunks left are even
	if (chunks.size() - startIndex % 2 == 0)
		return false;

	//checks if the first chunk is not intable or a variable
	if (!(Intable(chunks[startIndex]) || VariableExists(chunks[startIndex])))
		return false;

	//loops through two chunks at a time until the end
	for (int i = startIndex + 1; i < chunks.size(); i += 2) {

		//checks if this wasn't supported symbol
		auto it = std::find(supportedSymbols.begin(), supportedSymbols.end(), chunks[i]);
		if (it == supportedSymbols.end())
			return false;

		if (!(Intable(chunks[i + 1]) || VariableExists(chunks[i + 1])))
			return false;
	}
	return true;
}

std::string Kode::HandleFunction(int statementNumber, std::vector<std::string> chunks, int startIndex) {

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
				//if (debug)
					AddToConsoleOutput(i, "Tried to divide by zero. Division operation skipped", RED);
				continue;
			}

			result = Divide(result, toWorkWith);
		}
	}

	return std::to_string(result);
}


//To see instructions, go to the readme at https://github.com/KallumP/KallumOS/tree/readme#readme