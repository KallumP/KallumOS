#pragma once
#include "Process.h"
#include "FileSelector.h"

#include <vector>

class TestWindow : public Process {

public:

	TestWindow();
	TestWindow(Point _position, Point _size);

	void Draw(Point offset);

private:
	FileSelector fileSelector;
};

