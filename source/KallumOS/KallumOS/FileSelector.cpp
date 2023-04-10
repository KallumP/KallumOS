#include "FileSelector.h"

#include <iostream>

FileSelector::FileSelector() : Control() {}

FileSelector::FileSelector(Point _position, Point _size, std::filesystem::path appPath) : Control(_position, _size) {
	
	backColor = LIGHTGRAY;
	
	//generates the file path for this instance
	std::filesystem::path osPath = std::filesystem::current_path();
	osPath = osPath / "hardDrive";
	path = osPath / appPath;

	//checks if this path existed
	if (!std::filesystem::exists(path)) {
		std::cout << "Directory not found" << std::endl << "Creating directory now" << std::endl;
		
		//makes the file path
		if (!std::filesystem::create_directory(path)) {
			std::cout << "Failed to create directory\n";
			return;
		}
	}
}


void FileSelector::Draw() {

	//draws the button
	DrawRectangle(position.GetX(), position.GetY(), size.GetX(), size.GetY(), backColor);

	//draws the textbox value
	DrawText("File selector", position.GetX() + padding.GetX(), position.GetY() + padding.GetY(), fontSize, fontColor);

	DrawRectangleLines(position.GetX(), position.GetY(), size.GetX(), size.GetY(), BLACK);
}

bool FileSelector::Click(Point* mousePosition) {

	return false;
}
