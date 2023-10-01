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
	void OnMouseMove(Point* e);

private:

	void DrawBorders(Point offset, Point dimensions, Point boxSize);
	void DrawStrings(Point offset, Point dimensions, Point boxSize);
	void DrawMatrix(Point offset, Point dimensions, Point boxSize);
	void DrawPath(Point offset, Point dimensions, Point boxSize);

	void Go() {
		GenerateEmptyMatrix();
		FillMatrix();
		FindPath();
	}

	void GenerateEmptyMatrix();
	void FillMatrix();
	void FindPath();

	TextBox source;
	TextBox target;
	TextBox* focused;

	std::vector<std::vector<int>> distanceMatrix;
	std::vector<std::vector<std::string>> fromMatrix;
	std::vector<Point> path;

	std::string skip = "s";
	std::string insert = "i";
	std::string delete_ = "d";
	std::string nothing = "_";

};

