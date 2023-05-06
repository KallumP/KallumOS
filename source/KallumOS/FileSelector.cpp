#include "FileSelector.h"

#include <iostream>

FileSelector::FileSelector() : Control() {}

FileSelector::FileSelector(Point _position, Point _size, std::filesystem::path appPath) : Control(_position, _size) {

	backColor = LIGHTGRAY;

	operation = Operations::selectFile;
	submit = Button(Point(position.GetX() + 10, position.GetY() + 10), Point(50, 30), "Select");
	submit.ToggleCentered();
	submit.SetFontSize(10);

	//generates the file path for this instance
	std::filesystem::path osPath = std::filesystem::current_path();
	path = osPath / "hardDrive";
	path = path / appPath;

	if (!VerifyPath(path))
		return;

	fontSize = 10;

	FetchAllCurrentFiles();
}

bool FileSelector::VerifyPath(std::filesystem::path toCheck) {

	//checks if this path existed
	if (!std::filesystem::exists(toCheck)) {
		std::cout << "Directory not found" << std::endl << "Creating directory now" << std::endl;

		//makes the file path
		if (!std::filesystem::create_directory(toCheck)) {
			std::cout << "Failed to create directory\n";
			return false;
		}
	}

	return true;
}


void FileSelector::Draw(Point offset) {

	DrawRectangle(offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), size.GetX(), size.GetY(), backColor);


	DrawRectangleLines(offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), size.GetX(), size.GetY(), BLACK);

	offset.Add(Point(20, 20));

	submit.Draw();

	offset.Add(Point(0, 40));

	//draws the current file path
	std::string currentPath = "Current directory: " + std::filesystem::relative(path, std::filesystem::current_path()).string();
	DrawText(currentPath.c_str(), position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);
	offset.Add(Point(0, FileOption::ySize)); //moves the offset down by the text height


	offset.Add(Point(10, FileOption::ySize)); //indents the text and adds a gap between the texts
	DrawText("Directories", position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);
	offset.Add(Point(10, FileOption::ySize)); //indents the text moves the offset down by the text height

	for (int i = 0; i < currentDirectories.size(); i++)
		currentDirectories[i].Draw(offset);
	offset.Add(Point(0, currentDirectories.size() * FileOption::ySize)); // moves the offset by the amount of directories drawn


	offset.Add(Point(-10, FileOption::ySize)); //unindents the text and adds a gap between the directories and the files
	DrawText("Files", position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);
	offset.Add(Point(10, FileOption::ySize)); //indents and moves the text down by the text height

	for (int i = 0; i < currentFiles.size(); i++)
		currentFiles[i].Draw(offset);
	offset.Add(Point(0, currentFiles.size() * FileOption::ySize)); // moves the offset by the amount of files drawn

}

void FileOption::Draw(Point offset) {
	if (hovered)
		DrawText(fileName.c_str(), offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), fontSize, RED);
	else
		DrawText(fileName.c_str(), offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), fontSize, BLACK);
}


bool FileSelector::Hover(Point* mousePosition) {

	submit.Hover(mousePosition);

	DetectFileHover(mousePosition);

	return false;
}

bool FileSelector::Click(Point* mousePosition) {

	if (submit.Click(mousePosition))
		std::cout << " Clicked\n";

	SwithPath();

	return false;
}

void FileSelector::SwithPath() {


	std::string newPath = "";
	for (int i = 0; i < currentDirectories.size(); i++)
		if (currentDirectories[i].hovered)
			newPath = currentDirectories[i].fileName;

	for (int i = 0; i < currentFiles.size(); i++)
		if (currentFiles[i].hovered)
			newPath = currentFiles[i].fileName;


	if (newPath == "")
		return;

	std::filesystem::path pathToCheck = path / newPath;
	if (!VerifyPath(pathToCheck))
		return;

	path = pathToCheck;
	currentDirectories.clear();
	currentFiles.clear();
	FetchAllCurrentFiles();
}

//fetches all the files in the current file path
void FileSelector::FetchAllCurrentFiles() {

	//removes the previous files from the list
	currentFiles.clear();

	//loops through all the files in the current directory and adds them to the list
	for (const auto& entry : std::filesystem::directory_iterator(path))
		if (entry.is_regular_file())
			currentFiles.push_back(FileOption(std::filesystem::relative(entry.path(), path).string(), currentFiles.size(), position));
		else
			currentDirectories.push_back(FileOption(std::filesystem::relative(entry.path(), path).string(), currentDirectories.size(), position));

}

void FileSelector::DetectFileHover(Point* mousePosition) {

	//directories
	int listDisplayOffset = FileOption::ySize * 3 + 20 + 40;
	for (int i = 0; i < currentDirectories.size(); i++)
		if (mousePosition->GetY() > currentDirectories[i].position.GetY() + listDisplayOffset &&
			mousePosition->GetY() < currentDirectories[i].position.GetY() + listDisplayOffset + FileOption::ySize)
			currentDirectories[i].hovered = true;
		else
			currentDirectories[i].hovered = false;

	//files
	listDisplayOffset += currentDirectories.size() * FileOption::ySize;
	listDisplayOffset += FileOption::ySize * 2;
	for (int i = 0; i < currentFiles.size(); i++)
		if (mousePosition->GetY() > currentFiles[i].position.GetY() + listDisplayOffset &&
			mousePosition->GetY() < currentFiles[i].position.GetY() + listDisplayOffset + FileOption::ySize)
			currentFiles[i].hovered = true;
		else
			currentFiles[i].hovered = false;

}