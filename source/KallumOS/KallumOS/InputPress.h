#pragma once
#include "raylib.h"

#include <string>

class KeyPress {

public:

	KeyPress(int _keyCode, std::string _keyContent) {
		keyCode = _keyCode;
		keyContent = _keyContent;
	}
	int GetKeyCode() {
		return keyCode;
	}

	std::string GetKeyContent() {
		return keyContent;
	}

private:
	int keyCode;
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
	//olc::HWButton state;

	//mouse buttons are as follows
	//left: 0, right: 1, middle: 2
};