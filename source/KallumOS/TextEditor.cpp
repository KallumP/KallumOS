#include "TextEditor.h"

TextEditor::TextEditor(Point _position, Point _size) : Process("Text Editor", _position, _size) {

	text = "";

	open = Button(Point(30, 40), Point(100, 30), "Open");
	open.Tether(&position);
	open.SetFontSize(10);

	save = Button(Point(150, 40), Point(100, 30), "Save");
	save.Tether(&position);
	save.SetFontSize(10);

}

void TextEditor::Tick(float elapsedTime) {

	if (fileSelector != nullptr) {

		fileSelector->Hover(new Point(GetMouseX(), GetMouseY()));

	} else {

		open.Hover(new Point(GetMouseX(), GetMouseY()));
		save.Hover(new Point(GetMouseX(), GetMouseY()));

	}

}

void TextEditor::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		open.Draw();
		save.Draw();

		int padding = 10;
		offset.Add(Point(0, open.GetSize().GetY() + padding));

		//gets properties about the lines to draw to the window
		int textLength = text.size();
		int charsPerLine = (size.GetX() - padding * 2) / MeasureText("X", defaultFontSize);
		int linesToDraw = std::ceil(textLength / (float)charsPerLine);

		//if there wasn't enough characters to fill a line
		if (text.size() < charsPerLine) {
			DrawText(text.c_str(), padding + offset.GetX(), 10 + offset.GetY(), defaultFontSize, BLACK);

		} else {

			for (int i = 0; i < linesToDraw; i++) {

				std::string line;
				line = text.substr(i * charsPerLine, charsPerLine);

				DrawText(line.c_str(), padding + offset.GetX(), padding + (i * MeasureText("X", defaultFontSize)) + offset.GetY(), defaultFontSize, BLACK);
			}
		}

		if (fileSelector != nullptr)
			fileSelector->Draw(Point(0, 0));
	}
}

void TextEditor::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == KEY_BACKSPACE) {
		DeleteChar();
		return;
	} else if (e->GetKeyCode() == KEY_LEFT) {
		//MoveCursor(-1);
		return;
	} else if (e->GetKeyCode() == KEY_RIGHT) {
		//MoveCursor(1);
		return;
	}

	if (e->GetKeyContent().length() != 0)
		Input(e->GetKeyContent());
}

void TextEditor::OnMousePress(MousePress* e) {

	if (display) {

		SuperMousePress(NormaliseMousePos());

		if (fileSelector != nullptr) {

			fileSelector->Click(new Point(GetMouseX(), GetMouseY()));

			if (fileSelector->GetReady()) {

				LoadFromFile(fileSelector->GetSelectedFileName());

				delete fileSelector;
				fileSelector = nullptr;
			}

		} else {

			HandleButtonClicks();

			int checkOffset;

			//saves the height of the mouse
			Point normalisedMouse = NormaliseMousePos();

			//move cursore to something near the text
		}
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

//handles what happens if the open or save buttons are clicked
void TextEditor::HandleButtonClicks() {

	if (open.Click(new Point(GetMouseX(), GetMouseY()))) {
		std::filesystem::path appPath = "hardDrive/TextEditor";

		//if the path didn't exist
		if (!Helper::VerifyPathExists(appPath))

			//if the path could not be made
			if (!Helper::CreatePath(appPath))

				return;

		fileSelector = new FileSelector(Point(200, 100), Point(300, 300), appPath);
	}
}

//loads the content of the selected file into the text editor
void TextEditor::LoadFromFile(std::string selectedPath) {

	std::string fullPath = "hardDrive/TextEditor/" + selectedPath;

	//tries to open the selected file
	std::ifstream selectedFile;
	selectedFile.open(fullPath);

	//checks if the file was opened
	if (selectedFile.is_open()) {

		//loads each line
		std::string line;
		while (std::getline(selectedFile, line))
			
			//adds each line
			text += line;
		
		//loads the file
		selectedFile.close();

	} else 

		//adds the error message
		text = "Could not open file";
}