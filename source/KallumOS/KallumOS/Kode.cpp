#include "Kode.h"


Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	fontSize = 20;
	//text = "out Hello world!;out Hello second line!:);";
	text = "out x";

	consoleHeight = 100;
	AddToConsoleOutput(0, "Press F5 to compile your text", BLUE);
	AddToConsoleOutput(1, "Press F3 to off debug outputs", BLUE);

	debug = true;
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

			DrawText(text.c_str(), padding + offset.GetX(), offset.GetY() + padding + (GetNextLineY(lineCount)), fontSize, BLACK);
			lineCount++;

		} else {

			//gets the number of lines that need to be drawn for this statemenet
			int linesToDraw = std::ceil(text.size() / (float)charsPerLine);

			//loops through each line
			for (int i = 0; i < linesToDraw; i++) {

				std::string line;
				line = text.substr(i * charsPerLine, charsPerLine);

				DrawText(line.c_str(), padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(lineCount), fontSize, BLACK);
				lineCount++;
			}
		}
	}
}
void Kode::DrawConsole(Point offset) {

	int padding = 10;

	offset.SetY(offset.GetY() + size.GetY() - consoleHeight);
	DrawRectangle(offset.GetX(), offset.GetY(), size.GetX(), consoleHeight, BLACK);


	for (int i = 0; i < console.size(); i++) {

		//gets the string to output
		std::string text = "";
		text += std::to_string(console[i].linkedToStatement) + ". ";
		text += console[i].text;

		DrawText(text.c_str(), padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(i), fontSize, console[i].textColor);
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

void Kode::OnMousePress(MousePress* e, int taskbarHeight) {

	if (display) {

		SuperMousePress(NormaliseMousePos(taskbarHeight));

		int checkOffset;

		//saves the height of the mouse
		Point normalisedMouse = NormaliseMousePos(taskbarHeight);

		//move cursore to something near the text
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
				std::string functionResult = HandleFunction(chunks, 2);

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
			if (chunks.size() != 4) {
				if (debug)
					AddToConsoleOutput(i, "Need to have three operands for an int", RED);
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

			//if the value was not a number
			if (!Intable(chunks[3])) {
				if (debug)
					AddToConsoleOutput(i, "Value must be a number", RED);
				continue;
			}

			//declares and assigns values to the variable
			Variable* inter = new Variable();
			inter->identifier = chunks[1];
			inter->value = chunks[3];
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

				//if the value was not a number
				if (!Intable(chunks[2])) {
					if (debug)
						AddToConsoleOutput(i, "Value must be a number", RED);
					continue;
				}

				//assigns the value
				toAssign->value = chunks[2];

				if (debug)
					AddToConsoleOutput(i, "Integer: " + toAssign->identifier + " given value: " + toAssign->value, RED);
				continue;
			}
		}
	}
}

//returns what opcode or alias was called
std::string Kode::CheckOpcode(std::vector<std::string> chunks) {

	std::vector<std::string> supportedOpCodes;
	supportedOpCodes.push_back("out");
	supportedOpCodes.push_back("int");

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

	//list of supported symbols
	std::vector<std::string> supportedSymbols;
	supportedSymbols.push_back("+");

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

std::string Kode::HandleFunction(std::vector<std::string> chunks, int startIndex) {

	//tries to find a variable with this value
	Variable* potentialVariable = GetVariable(chunks[1]);

	//if a variable was found
	if (potentialVariable != nullptr) {
		return potentialVariable->value;
	}
}


//instructions
//pressing f5 will compile the kode
//pressing f3 will make most functionality output to the console in red
// 
//kode consists of statements
// a statement is ended by a ;
//each statement consists of chunks
// chunk are to be separated by a space
//the first chunk is the opcode (or variable name)
//this is what states what will happen next
// 
// 
//the "out" opcode will take whatever is after it and output it to the console
// if the following chunks are just a variable identifier, if that identifier exists, output it's value
// else output all chunks as string literal
// 
// 
//the "int" opcode will declare and assign a new integer variable
//the second chunk is the variable identifier
//the third chunk is the  = symbol
//the fourth chunk is the variable value
//Declaration must follow <type> <identifier> = <value>.
//
//a variable identifier initiates works as an alias to the assign opcode
//assign cannot be called directly
//the second chunk must be an = symbol
//the third chunk must be a value that can be turned into the variable type that is being assigned to
//
//
//A valid function will have an odd number of chunks
//A valid function will start with either a number or a variable name, 
// and then follow with a supported symbol like (+, -. /, *) + a number or variable name
//It will continue the previous step until the end of the list.

