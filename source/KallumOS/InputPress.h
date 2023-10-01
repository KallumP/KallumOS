#pragma once
#include "raylib.h"
#include "Helper.h"

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
		mousePosition = Helper::GetMousePosition();
	}

	int GetMouseCode() {
		return mouseButton;
	}

	void SetMousePosition() {
		mousePosition = Helper::GetMousePosition();
	}

	Point* GetMousePosition() {
		return &mousePosition;
	}

private:
	int mouseButton;
	Point mousePosition;
	//mouse buttons are as follows
	//left: 0, right: 1, middle: 2
};