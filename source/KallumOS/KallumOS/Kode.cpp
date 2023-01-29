#include "Kode.h"


Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	fontSize = 20;
	text = "out Hello world!;out Hello second line!:);";

	consoleHeight = 100;
	console.push_back("Press F5 to compile your text");
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
		text += std::to_string(i) + ". ";
		text += console[i];

		DrawText(text.c_str(), padding + offset.GetX(), offset.GetY() + padding + GetNextLineY(i), fontSize, WHITE);
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

		console.push_back("");

		//checks if this was an empty statement
		if (statements[i].size() == 0) {
			console[i] = ("Empty statement");
			continue;
		}

		//splits the statement into the different chunks (defined by ' ')
		std::vector<std::string> chunks = Split(statements[i], " ");

		//gets what the first chunk was
		std::string foundOpcode = CheckOpcode(chunks);

		//unknown opcode
		if (foundOpcode == "error") {
			console[i] = ("Unrecognized opcode");
			continue;
		}

		//empty opcode
		if (foundOpcode == "empty") {
			console[i] = ("Empty opcode (Maybe you have a space at the start?)");
			continue;
		}

		//out command
		if (foundOpcode == "out") {

			//loops through all the chunks
			for (int j = 1; j < chunks.size(); j++) {

				console[i] += chunks[j] + " ";
				continue;
			}
			continue;
		}

		//int command
		if (foundOpcode == "int") {

			//not enough operands
			if (chunks.size() != 3) {

				console[i] = ("Need to have two operands for an int");
				continue;
			}

			//identifier operand is empty
			if (chunks[1] == "") {

				console[i] = ("Cannot have empty variable identifier");
				continue;
			}

			//tries to convert the value operand into an int
			bool cannotConvert = false;
			int value;
			try {
				value = std::stoi(chunks[2]);
			} catch (const std::invalid_argument& e) {
				cannotConvert = true;
			}

			//if the value operand was not a number
			if (cannotConvert) {

				console[i] = ("Value must be a number");
				continue;
			}


			Integer* inter = new Integer();
			inter->identifier = chunks[1];
			inter->value = value;
			variables.push_back(inter);
			console[i] = ("Integer: " + inter->identifier + " with value: " + std::to_string( inter->value) + " created");
			continue;
		}
	}
}

std::string Kode::CheckOpcode(std::vector<std::string> chunks) {

	std::vector<std::string> supportedOpCodes;
	supportedOpCodes.push_back("out");
	supportedOpCodes.push_back("int");

	auto it = std::find(supportedOpCodes.begin(), supportedOpCodes.end(), chunks[0]);
	if (it != supportedOpCodes.end())
		return chunks[0];
	else if (chunks[0] == "")
		return "empty";
	else
		return "error";
}

