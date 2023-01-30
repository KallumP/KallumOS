#pragma once
#include "raylib.h"

#include <string>

class KeyPress {

public:

	KeyPress(int _keyCode, std::string _keyContent) {
		keyCode = _keyCode;
		keyContent = _keyContent;
		primaryContent = _keyContent;
		secondKeyContent = _keyContent;
	}
	KeyPress(int _keyCode, std::string _keyContent, std::string _secondKeyContent) {
		keyCode = _keyCode;
		keyContent = _keyContent;
		primaryContent = _keyContent;
		secondKeyContent = _secondKeyContent;
	}

	int GetKeyCode() {
		return keyCode;
	}

	std::string GetKeyContent() {
		return keyContent;
	}

	void UsePrimary() { keyContent = primaryContent; }
	void UseSecondary() { keyContent = secondKeyContent; }

private:
	int keyCode;
	std::string keyContent;
	std::string primaryContent;
	std::string secondKeyContent;


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
	//mouse buttons are as follows
	//left: 0, right: 1, middle: 2
};