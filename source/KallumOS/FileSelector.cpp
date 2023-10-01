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

bool FileSelector::OnMousePress(MousePress* e) {

	//select button was clicked
	if (submit.OnMousePress(e)) {
		SetData();
		return false;
	}

	//button not clicked means not ready
	ready = false;

	HandleFileClick();

	return false;
}

bool FileSelector::OnMouseMove(Point* e) {

	submit.OnMouseMove(e);

	FileViewer::DetectFileHover(e);

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

	if (selectedFile != nullptr)
		ready = true;
}