#include "Kode.h"


Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	fontSize = 20;
	//text = "out Hello world!;out Hello second line!:);";
	text = "out Hello world!;out Hello second line!:);int test 10;test = 4";

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
			if (chunks.size() != 3) {
				if (debug)
					AddToConsoleOutput(i, "Need to have two operands for an int", RED);
				continue;
			}

			//identifier is empty
			if (chunks[1] == "") {
				if (debug)
					AddToConsoleOutput(i, "Cannot have empty variable identifier", RED);
				continue;
			}

			//tries to convert the value into an int
			bool cannotConvert = false;
			int value;
			try {
				value = std::stoi(chunks[2]);
			} catch (const std::invalid_argument& e) {
				cannotConvert = true;
			}

			//if the value was not a number
			if (cannotConvert) {
				if (debug)
					AddToConsoleOutput(i, "Value must be a number", RED);
				continue;
			}


			Variable* inter = new Variable();
			inter->identifier = chunks[1];
			inter->value = std::to_string(value);
			inter->type = "integer";
			variables.push_back(inter);

			if (debug)
				AddToConsoleOutput(i, "Integer: " + inter->identifier + " with value: " + inter->value + " created", RED);
			continue;
		}

		//int command
		if (foundOpcode == "ass") {

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

			//gets the variable being assigned
			int variableIndex;
			for (int i = 0; i < variables.size(); i++)
				if (chunks[0] == variables[i]->identifier) {
					variableIndex = i;
					continue;
				}
			Variable* toAssign = variables[variableIndex];

			if (toAssign->type == "integer") {


				//tries to convert the value into an int
				bool cannotConvert = false;
				int value;
				try {
					value = std::stoi(chunks[2]);
				} catch (const std::invalid_argument& e) {
					cannotConvert = true;
				}

				//if the value was not a number
				if (cannotConvert) {
					if (debug)
						AddToConsoleOutput(i, "Value must be a number", RED);
					continue;
				}

				toAssign->value = std::to_string(value);

				if (debug)
					AddToConsoleOutput(i, "Integer: " + toAssign->identifier + " given value: " + toAssign->value, RED);
				continue;
			}
		}
	}
}

std::string Kode::CheckOpcode(std::vector<std::string> chunks) {

	std::vector<std::string> supportedOpCodes;
	supportedOpCodes.push_back("out");
	supportedOpCodes.push_back("int");

	//returns if a valid opcode was found
	auto it = std::find(supportedOpCodes.begin(), supportedOpCodes.end(), chunks[0]);
	if (it != supportedOpCodes.end())
		return chunks[0];

	//returns if a variable identifier was found
	for (int i = 0; i < variables.size(); i++)
		if (chunks[0] == variables[i]->identifier)
			return "ass";

	if (chunks[0] == "")
		return "empty";

	return "error";
}

void Kode::AddToConsoleOutput(int statementNumber, std::string toAdd, Color textColor) {

	ConsoleText ct;
	ct.linkedToStatement = statementNumber;
	ct.text = toAdd;
	ct.textColor = textColor;

	console.push_back(ct);
}
