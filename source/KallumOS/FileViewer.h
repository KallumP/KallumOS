#pragma once
#include "Helper.h"
#include "Control.h"

#include <filesystem>
#include <vector>

struct FileOption {
	std::string fileName;
	std::filesystem::path filePath;
	Point position;
	bool hovered = false;
	static const int ySize = 20;
	int fontSize;
	Color fontColor;

	FileOption(std::string _fileName, int index, Point controlPosition, std::filesystem::path _filePath)
	{
		filePath = _filePath;
		fileName = _fileName;
		position = controlPosition;
		position.Add(Point(0, index * ySize));

		fontSize = 10;
		fontColor = BLACK;
	}

	void Draw(Point offset);
};

class FileViewer : public Control {

public: 

	FileViewer();
	FileViewer(Point _position, Point _size, std::filesystem::path appPath);

	void Draw(Point offset);
	bool Hover(Point* mousePosition);
	bool Click(Point* mousePosition);


protected:
	void HandleFileClick();
	void FetchAllCurrentFiles();
	void DetectFileHover(Point* mousePosition);


	std::filesystem::path path;
	std::vector<FileOption> currentFiles;
	std::vector<FileOption> currentDirectories;
};

