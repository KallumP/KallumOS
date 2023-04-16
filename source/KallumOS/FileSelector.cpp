#include "FileSelector.h"

#include <iostream>

FileSelector::FileSelector() : Control() {}

FileSelector::FileSelector(Point _position, Point _size, std::filesystem::path appPath) : Control(_position, _size) {

	backColor = LIGHTGRAY;

	//generates the file path for this instance
	std::filesystem::path osPath = std::filesystem::current_path();
	path = osPath / "hardDrive";
	path = path / appPath;

	//checks if this path existed
	if (!std::filesystem::exists(path)) {
		std::cout << "Directory not found" << std::endl << "Creating directory now" << std::endl;

		//makes the file path
		if (!std::filesystem::create_directory(path)) {
			std::cout << "Failed to create directory\n";
			return;
		}
	}

	fileOptionHeight = 20;

	FetchAllCurrentFiles();
}


void FileSelector::Draw(Point offset) {

	DrawRectangle(offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), size.GetX(), size.GetY(), backColor);


	DrawRectangleLines(offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), size.GetX(), size.GetY(), BLACK);

	offset.Add(Point(20, 20));

	//draws the current file path
	std::string currentPath = "Current directory: " + std::filesystem::relative(path, std::filesystem::current_path()).string();
	DrawText(currentPath.c_str(), position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);



	offset.Add(Point(10, fileOptionHeight));
	DrawText("Files", position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);
	offset.Add(Point(0, fileOptionHeight));


	for (int i = 0; i < currentDirectories.size(); i++)
		DrawText(currentDirectories[i].c_str(), position.GetX() + offset.GetX(), position.GetY() + offset.GetY() + i * fileOptionHeight, fontSize, BLACK);

	int directoriesDrawn = currentDirectories.size() + 1;

	for (int i = 0; i < currentFiles.size(); i++)
		DrawText(currentFiles[i].c_str(), position.GetX() + offset.GetX(), position.GetY() + offset.GetY() + (i + directoriesDrawn) * fileOptionHeight, fontSize, BLACK);

}


bool FileSelector::Hover(Point* mousePosition) {

	return false;
}

bool FileSelector::Click(Point* mousePosition) {

	return false;
}



//fetches all the files in the current file path
void FileSelector::FetchAllCurrentFiles() {

	//removes the previous files from the list
	currentFiles.clear();

	//loops through all the files in the current directory and adds them to the list
	for (const auto& entry : std::filesystem::directory_iterator(path))
		if (entry.is_regular_file())
			currentFiles.push_back(std::filesystem::relative(entry.path(), path).string());
		else
			currentDirectories.push_back(std::filesystem::relative(entry.path(), path).string());

}