#pragma once

#include "Control.h"
#include <filesystem>

struct Hovered {
	bool file;
	int index;
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
	std::vector<std::string> currentFiles;
	std::vector<std::string> currentDirectories;
	int fileOptionHeight;
	void FetchAllCurrentFiles();
};

