#pragma once
#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Control.h"
#include "KeyPress.h" 

#include <vector>
#include <string>


class Input {

public:
	Input(olc::PixelGameEngine*);
	//void GenerateKeyList();
	void GenerateKeyPressList();
	void GetKeyPress(KallumOS*);

private:

	olc::PixelGameEngine* window;

	//std::vector<olc::Key> allKeys;

	std::vector<KeyPress> textPresses;
	std::vector<KeyPress> modifierPresses;
	std::vector<KeyPress> specialPresses;

};



class MousePress {

};