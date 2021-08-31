#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "State.h"
#include "InputPress.h"
 
#include <vector>

class KallumOS {

public:

	KallumOS(olc::PixelGameEngine*);
	~KallumOS();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);
	void OnMouseHold(MousePress*);
	void OnMousePress(MousePress*);

private:

	void SwitchStates();

	olc::PixelGameEngine* window;
	State* state;
};