#pragma once
#include "olcPixelGameEngine.h"

#include <string>

class KeyPress {

public:

	KeyPress(olc::Key _keyCode, std::string _keyContent) {
		keyCode = _keyCode;
		keyContent = _keyContent;
	}
	olc::Key GetKeyCode() {
		return keyCode;
	}

	std::string GetKeyContent() {
		return keyContent;
	}

	static bool ctrlPressed;
	static bool shiftPressed;
	static bool altPressed;

private:
	olc::Key keyCode;
	std::string keyContent;

};