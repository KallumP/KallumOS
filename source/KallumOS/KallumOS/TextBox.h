#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"


#include <string>
#include <vector>

class TextBox : public Control {

public:

	TextBox(olc::PixelGameEngine*, Point, Point, std::string);

	void Draw();
	bool Click(Point*);
	void OnKeyPress(KeyPress*);



private:

	void Append(char input);
	void DeleteOne();
	void DeleteWord();
	void FindNewCursorPosition(int);

	int cursorPosition;
};


