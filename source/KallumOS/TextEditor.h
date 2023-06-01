#pragma once
#include "Process.h"
#include "Button.h"
#include "FileSelector.h"

#include <fstream>
#include <iostream>
#include <string>

class TextEditor : public Process {

public:

	TextEditor();
	TextEditor(Point _position, Point _size);

	void Tick(float elapsedTime);
	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);

private:

	void Input(std::string input);
	void DeleteChar();
	void HandleButtonClicks();

	void LoadFromFile(std::string selectedPath);

	std::string text;

	int cursor;

	Button open;
	Button save;
	FileSelector *fileSelector;
};

