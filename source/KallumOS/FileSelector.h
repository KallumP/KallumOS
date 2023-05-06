#pragma once

#include "Control.h"
#include "Button.h"
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

	bool GetReady() { return ready; }

private:

	std::filesystem::path path;
	std::vector<FileOption> currentFiles;
	std::vector<FileOption> currentDirectories;
	std::filesystem::path selectedFile;

	bool VerifyPath(std::filesystem::path toCheck);
	void SwithPath();
	void FetchAllCurrentFiles();
	void DetectFileHover(Point* mousePosition);

	void SetData();

	enum class Operations {selectFile, selectDir, newFile};
	Operations operation;
	bool ready;

	Button submit;
};

