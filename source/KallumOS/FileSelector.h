#pragma once

#include "Control.h"
#include "Button.h"
#include <filesystem>

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

class FileSelector : public Control {

public:

	FileSelector();
	FileSelector(Point _position, Point _size, std::filesystem::path appPath);

	void Draw(Point offset);
	bool Hover(Point* mousePosition);
	bool Click(Point* mousePosition);

	bool GetReady() { return ready; }
	std::string GetSelectedFile() { return selectedFile.string(); }

private:

	std::filesystem::path path;
	std::vector<FileOption> currentFiles;
	std::vector<FileOption> currentDirectories;
	std::filesystem::path selectedFile;

	bool VerifyPathExists(std::filesystem::path toCheck);
	bool CreatePath(std::filesystem::path toCheck);
	void HandleFileClick();
	void FetchAllCurrentFiles();
	void DetectFileHover(Point* mousePosition);

	void SetData();

	enum class Operations {selectFile, selectDir, newFile};
	Operations operation;
	bool ready;

	Button submit;
};

