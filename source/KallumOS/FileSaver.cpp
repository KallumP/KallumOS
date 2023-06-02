#include "FileSaver.h"


FileSaver::FileSaver() : FileViewer() {

}

FileSaver::FileSaver(Point _position, Point _size, std::filesystem::path appPath) : FileViewer(_position, _size, appPath) {

	ready = false;

	submit = Button(Point(10, 10), Point(50, 30), "Save");
	submit.Tether(&position);
	submit.SetFontSize(10);

	name = TextBox(Point(70, 10), Point(200, 30), "", "File name");
	name.Tether(&position);
	name.SetFontSize(10);
}

void FileSaver::Draw(Point offset) {

	//draws the files and directories
	FileViewer::Draw(Point(0, 0));

	offset.Add(Point(20, 20));

	//draws the button
	submit.Draw();
	name.Draw();
}

bool FileSaver::Hover(Point* mousePosition) {

	submit.Hover(mousePosition);
	name.Hover(mousePosition);
	FileViewer::DetectFileHover(mousePosition);

	return false;
}


bool FileSaver::Click(Point* mousePosition) {

	//select button was clicked
	if (submit.Click(mousePosition)) {
		SetData();
		return false;
	}

	//button not clicked means not ready
	ready = false;

	name.Click(mousePosition);

	HandleFileClick();

	return false;
}


void FileSaver::HandleFileClick() {

	//checks if a new file was clicked into
	for (int i = 0; i < currentFiles.size(); i++) {

		if (currentFiles[i].hovered) {
			name.SetValue(currentFiles[i].fileName);
			currentFiles[i].fontColor = BLACK;
		}
	}

	FileViewer::HandleFileClick();
}


void FileSaver::SetData() {

	if (name.GetValue() != "")
		ready = true;
}

void FileSaver::OnKeyPress(KeyPress* e) {
	name.OnKeyPress(e);
}