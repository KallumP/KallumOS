#include "kGraphics.h"
#include "FileViewer.h"

FileViewer::FileViewer() : Control() {

}

FileViewer::FileViewer(Point _position, Point _size, std::filesystem::path appPath) : Control(_position, _size) {

	backColor = LIGHTGRAY;
	fontSize = 10;

	//generates the file path for this instance
	std::filesystem::path osPath = std::filesystem::current_path();
	path = osPath / appPath;

	//if the path didn't exist
	if (!Helper::VerifyPathExists(path))
		return;

	FetchAllCurrentFiles();
}

void FileViewer::Draw(Point offset) {

	kGraphics::FillRect(offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), size.GetX(), size.GetY(), backColor);

	kGraphics::DrawRect(offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), size.GetX(), size.GetY(), BLACK);

	offset.Add(Point(20, 20));

	//button offset
	offset.Add(Point(0, 40));

	//draws the current file path
	std::string currentPath = "Current directory: " + std::filesystem::relative(path, std::filesystem::current_path()).string();
	kGraphics::DrawString(currentPath, position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);
	offset.Add(Point(0, FileOption::ySize)); //moves the offset down by the text height


	offset.Add(Point(10, FileOption::ySize)); //indents the text and adds a gap between the texts
	kGraphics::DrawString("Directories", position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);
	offset.Add(Point(10, FileOption::ySize)); //indents the text moves the offset down by the text height

	//draws the directories
	for (int i = 0; i < currentDirectories.size(); i++)
		currentDirectories[i].Draw(offset);
	offset.Add(Point(0, currentDirectories.size() * FileOption::ySize)); // moves the offset by the amount of directories drawn


	offset.Add(Point(-10, FileOption::ySize)); //unindents the text and adds a gap between the directories and the files
	kGraphics::DrawString("Files", position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), fontSize, BLACK);
	offset.Add(Point(10, FileOption::ySize)); //indents and moves the text down by the text height

	//draws the files
	for (int i = 0; i < currentFiles.size(); i++)
		currentFiles[i].Draw(offset);
	offset.Add(Point(0, currentFiles.size() * FileOption::ySize)); // moves the offset by the amount of files drawn
}

void FileOption::Draw(Point offset) {
	if (hovered)
		kGraphics::DrawString(fileName, offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), fontSize, RED);
	else
		kGraphics::DrawString(fileName, offset.GetX() + position.GetX(), offset.GetY() + position.GetY(), fontSize, fontColor);
}

bool FileViewer::OnMousePress(MousePress* e) {

	HandleFileClick();

	return false;
}

bool FileViewer::OnMouseMove(Point* e) {

	DetectFileHover(e);

	return false;
}

//handles what happens when a file or directory is clicked on
void FileViewer::HandleFileClick() {

	//todo: maybe handle clicking on a file to open it?

	//checks if a new directory was clicked into
	std::string newPath = "";
	for (int i = 0; i < currentDirectories.size(); i++)
		if (currentDirectories[i].hovered)
			newPath = currentDirectories[i].fileName;

	//if a directory was not clicked into, do nothing
	if (newPath == "")
		return;

	//if the directory clicked is not valid do nothing
	std::filesystem::path pathToCheck = path / newPath;
	if (!Helper::VerifyPathExists(pathToCheck))
		return;

	//sets the new file path and fetches its sub files
	path = pathToCheck;
	currentDirectories.clear();
	currentFiles.clear();
	FetchAllCurrentFiles();
}

//fetches all the files in the current file path
void FileViewer::FetchAllCurrentFiles() {

	//removes the previous files from the list
	currentFiles.clear();

	//loops through all the files in the current directory and adds them to the list
	for (const auto& entry : std::filesystem::directory_iterator(path))
		if (entry.is_regular_file())
			currentFiles.push_back(FileOption(std::filesystem::relative(entry.path(), path).string(), currentFiles.size(), position, entry.path()));
		else
			currentDirectories.push_back(FileOption(std::filesystem::relative(entry.path(), path).string(), currentDirectories.size(), position, entry.path()));
}

void FileViewer::DetectFileHover(Point* mousePosition) {

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
