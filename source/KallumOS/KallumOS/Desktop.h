#pragma once
#include "olcPixelGameEngine.h"
#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"

class Desktop : public State {

public: 
	Desktop(olc::PixelGameEngine*);
	~Desktop();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);
	void OnMousePress(MousePress*);


private:

	void Click();
	void MouseMove();

	olc::Pixel backgroundColor;

};

