#include "Kode.h"


Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	fontSize = 20;
	text = "out Hello World!;out This is the next line";

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
		std::string text = statements[i];
		if (i != statements.size() - 1)
			text += ";";


		//if there wasn't enough characters to fill a line
		if (text.size() < charsPerLine) {

			DrawText(text.c_str(), padding + offset.GetX(), offset.GetY() + padding + (lineCount * MeasureText("X", defaultFontSize) * 3), fontSize, BLACK);
			lineCount++;

		} else {

			//gets the number of lines that need to be drawn for this statemenet
			int linesToDraw = std::ceil(text.size() / (float)charsPerLine);

			//loops through each line
			for (int i = 0; i < linesToDraw; i++) {

				std::string line;
				line = text.substr(i * charsPerLine, charsPerLine);

				DrawText(line.c_str(), padding + offset.GetX(), offset.GetY() + padding + (lineCount * MeasureText("X", defaultFontSize) * 3), fontSize, BLACK);
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

		DrawText(console[i].c_str(), padding + offset.GetX(), padding + (i * MeasureText("X", defaultFontSize) * 3) + offset.GetY(), fontSize, WHITE);
	}

}


void Kode::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == KEY_BACKSPACE) {
		DeleteChar();
		return;
	} else if (e->GetKeyCode() == KEY_LEFT) {
		MoveCursor(-1);
		return;
	} else if (e->GetKeyCode() == KEY_RIGHT) {
		MoveCursor(1);
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

void Kode::Run() {

	console.clear();
	//console.push_back(text);

	//splits the text into statements (defined by ';')
	std::vector<std::string> statements = Split(text, ";");

	//loops through each statement
	for (int i = 0; i < statements.size(); i++) {

		console.push_back("");

		//splits the statement into the different chunks (defined by ' ')
		std::vector<std::string> chunks = Split(statements[i], " ");

		std::string compileState = "opCodeSearching";
		for (int j = 0; j < chunks.size(); j++) {

			if (compileState == "opCodeSearching") {

				if (chunks[j] == "out") {

					compileState = "operandSearch";
				}

			} else if (compileState == "operandSearch") {

				console[i] += chunks[j] + " ";
			}
		}
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