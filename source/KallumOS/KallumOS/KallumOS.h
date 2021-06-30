#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"

#include <vector>

class KallumOS {

public:

	KallumOS();
	KallumOS(olc::PixelGameEngine*);
	~KallumOS();

	void Tick(float);
	void Draw();

private:

	void Click();
	void MouseMove();
	void Focus(Control*);

	olc::PixelGameEngine* window;
	std::vector<Control*> controls;

	Point* mousePosition;
	bool mouseClicked;
	Control* focused;

};