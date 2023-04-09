#pragma once

#include "Control.h"


class FileSelector : public Control {

public:

	FileSelector();
	FileSelector(Point _position, Point _size);

	void Draw();
	bool Click(Point* mousePosition);

};

