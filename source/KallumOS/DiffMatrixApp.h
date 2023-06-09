#pragma once
#include "Process.h"
#include "TextBox.h"
#include "Button.h"
#include "Helper.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class DiffMatrixApp : public Process {

public:

	DiffMatrixApp();
	DiffMatrixApp(Point _position, Point _size);

	void Tick(float elapsedTime);
	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);

private:

	void DrawBorders(Point offset, Point dimensions, Point boxSize);
	void DrawStrings(Point offset, Point dimensions, Point boxSize);

	void Go() {
		GenerateEmptyMatrix();
		FillMatrix();
		OutputMatrix();
	}

	void GenerateEmptyMatrix();
	void FillMatrix();
	void OutputMatrix();

	Button go;
	TextBox source;
	TextBox target;
	TextBox* focused;

	std::vector<std::vector<int>> distanceMatrix;
	std::vector<std::vector<std::string>> fromMatrix;

	std::string skip = "s";
	std::string insert = "i";
	std::string delete_ = "d";
	std::string nothing = "_";

};

