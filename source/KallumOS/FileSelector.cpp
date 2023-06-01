#include "FileSelector.h"

#include <iostream>

FileSelector::FileSelector() : FileViewer() {}

FileSelector::FileSelector(Point _position, Point _size, std::filesystem::path appPath) : FileViewer(_position, _size, appPath) {

	ready = false;

	submit = Button(Point(10, 10), Point(50, 30), "Select");
	submit.Tether(&position);
	submit.SetFontSize(10);
}


void FileSelector::Draw(Point offset) {

	//draws the files and directories
	FileViewer::Draw(Point(0, 0));

	offset.Add(Point(20, 20));

	//draws the button
	submit.Draw();

}


bool FileSelector::Hover(Point* mousePosition) {

	submit.Hover(mousePosition);

	FileViewer::DetectFileHover(mousePosition);

	return false;
}

bool FileSelector::Click(Point* mousePosition) {

	//select button was clicked
	if (submit.Click(mousePosition)) {
		SetData();
		return false;
	}

	//button not clicked means not ready
	ready = false;

	HandleFileClick();

	return false;
}

void FileSelector::HandleFileClick() {

	//checks if a new file was clicked into
	for (int i = 0; i < currentFiles.size(); i++) {

		if (currentFiles[i].hovered) {
			selectedFile = &currentFiles[i];
			currentFiles[i].fontColor = BLUE;
			return;
		} else {
			currentFiles[i].fontColor = BLACK;
		}
	}

	FileViewer::HandleFileClick();
}


void FileSelector::SetData() {

	if (selectedFile->filePath != L"")
		ready = true;
}