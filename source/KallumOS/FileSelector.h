#pragma once

#include "Control.h"
#include <filesystem>

struct FileOption {
	std::string fileName;
	Point position;
	bool hovered = false;
	static const int ySize = 20;
	int fontSize;

	FileOption(std::string _fileName, int index, Point controlPosition)
	{
		fileName = _fileName;
		position = controlPosition;
		position.Add(Point(0, index * ySize));

		fontSize = 10;
	}

	void Draw(Point offset);
};

class FileSelector : public Control {

public:

	FileSelector();
	FileSelector(Point _position, Point _size, std::filesystem::path appPath);

	void Draw(Point offset);
	bool Hover(Point* mousePosition);
	bool Click(Point* mousePosition);

private:

	std::filesystem::path path;
	std::vector<FileOption> currentFiles;
	std::vector<FileOption> currentDirectories;

	void SwithPath(std::string newPath);
	void FetchAllCurrentFiles();
	void DetectFileHover(Point* mousePosition);
};

