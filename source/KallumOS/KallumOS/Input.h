#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include <vector>
class Input {

public:
	Input();
	void GenerateKeyList();
	void GetKeyPress(olc::PixelGameEngine* window, Control* control);

private:

	std::vector<olc::Key> allKeys;

};
