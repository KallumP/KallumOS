#pragma once

#include "Control.h"
#include <filesystem>


class FileSelector : public Control {

public:

	FileSelector();
	FileSelector(Point _position, Point _size, std::filesystem::path appPath);

	void Draw();
	bool Click(Point* mousePosition);

private:
	std::filesystem::path path;
};

