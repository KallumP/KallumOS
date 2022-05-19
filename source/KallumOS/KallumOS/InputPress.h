#pragma once
#include "raylib.h"

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

private:
	olc::Key keyCode;
	std::string keyContent;

};

class MousePress {

public:

	MousePress(int _mouseButton) {
		mouseButton = _mouseButton;
	}

	int GetMouseCode() {
		return mouseButton;
	}

private:
	int mouseButton;
	olc::HWButton state;

	//mouse buttons are as follows
	//left: 0, right: 1, middle: 2
};