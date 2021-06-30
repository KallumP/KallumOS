#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"

#include <vector>

class State
{
protected:
	olc::PixelGameEngine* window;
	std::vector<Control*> controls;

	Point* mousePosition;
	bool mouseClicked;
	Control* focused;

public:

	State(olc::PixelGameEngine*);
	~State();

	virtual void Tick(float) = 0;
	virtual void Draw() = 0;

	virtual	void Click() = 0;
	virtual void MouseMove() = 0;

	void Focus(Control*);

private:


};
