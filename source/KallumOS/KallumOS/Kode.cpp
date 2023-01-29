#include "Kode.h"


Kode::Kode(Point _position, Point _size) : Process("Kode", _position, _size) {

	fontSize = 20;
	text = "Hello World!";

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

	//gets properties about the lines to draw to the window
	int textLength = text.size();
	int charsPerLine = (size.GetX() - padding * 2) / MeasureText("X", fontSize);
	int linesToDraw = std::ceil(textLength / (float)charsPerLine);

	//if there wasn't enough characters to fill a line
	if (text.size() < charsPerLine) {
		DrawText(text.c_str(), padding + offset.GetX(), 10 + offset.GetY(), fontSize, BLACK);

	} else {

		for (int i = 0; i < linesToDraw; i++) {

			std::string line;
			line = text.substr(i * charsPerLine, charsPerLine);

			DrawText(line.c_str(), padding + offset.GetX(), padding + (i * MeasureText("X", defaultFontSize) * 3) + offset.GetY(), fontSize, BLACK);
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

		//std::cout << "Pressed: Backspace" << std::endl;

	} else {

		//std::cout << "Pressed: Backspace; There was nothing to delete" << std::endl;
	}
}

void Kode::Run() {
	console.clear();
	console.push_back(text);
}