#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "State.h"
#include "KeyPress.h"
 
#include <vector>

class KallumOS {

public:

	KallumOS(olc::PixelGameEngine*);
	~KallumOS();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);

private:

	olc::PixelGameEngine* window;
	State* state;
};