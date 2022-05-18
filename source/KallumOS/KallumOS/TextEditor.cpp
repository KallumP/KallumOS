#include "TextEditor.h"


TextEditor::TextEditor(olc::PixelGameEngine* _window, Point _position, Point _size) : Process(_window, "Text Editor", _position, _size) {

	text = "";
	fontSize = 2;

}


void TextEditor::Draw(Point offset) {

	DrawBoxBar(offset, true);
	offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

	int padding = 10;

	//gets properties about the lines to draw to the window
	int textLength = text.size();
	int charsPerLine = (size.GetX() - padding * 2) / (fontSize * 8);
	int linesToDraw = std::ceil(textLength / (float)charsPerLine);

	//if there wasn't enough characters to fill a line
	if (text.size() < charsPerLine) {
		window->DrawString(padding + offset.GetX(), 10 + offset.GetY(), text, olc::BLACK, fontSize);

	} else {

		for (int i = 0; i < linesToDraw; i++) {

			std::string line;
			line = text.substr(i * charsPerLine, charsPerLine);
				window->DrawString(padding + offset.GetX(), padding + (i * (fontSize * 8)) + offset.GetY(), line, olc::BLACK, fontSize);

		}
	}
}



void TextEditor::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == olc::Key::BACK) {
		DeleteChar();
		return;
	} else if (e->GetKeyCode() == olc::Key::LEFT) {
		//MoveCursor(-1);
		return;
	} else if (e->GetKeyCode() == olc::Key::RIGHT) {
		//MoveCursor(1);
		return;
	}

	if (e->GetKeyContent().length() != 0)
		Input(e->GetKeyContent());
}


void TextEditor::OnMousePress(MousePress* e, int taskbarHeight) {

	if (display) {

		CheckIfMinimizeClicked(NormaliseMousePos(taskbarHeight));

		int checkOffset;

		//saves the height of the mouse
		Point normalisedMouse = NormaliseMousePos(taskbarHeight);

		//move cursore to something near the text
	}
}

void TextEditor::Input(std::string input) {
	text.append(input);
}
void TextEditor::DeleteChar() {

	if (text.length() != 0) {

		text.pop_back();

		std::cout << "Pressed: Backspace" << std::endl;

	} else {

		std::cout << "Pressed: Backspace; There was nothing to delete" << std::endl;
	}
}