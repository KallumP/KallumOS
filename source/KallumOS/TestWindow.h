#pragma once
#include "Process.h"
#include "FileSelector.h"

#include <vector>

class TestWindow : public Process {

public:

	TestWindow(Point _position, Point _size);

	void Draw(Point offset);
	void Tick(float elapsedTime);
	void OnMousePress(MousePress* e);

private:
	FileSelector *fileSelector;
	std::string foo;
};

