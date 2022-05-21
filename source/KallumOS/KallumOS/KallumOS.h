#pragma once
#include "raylib.h"

#include "Control.h"
#include "State.h"
#include "InputPress.h"
 
#include <vector>

class KallumOS {

public:

	KallumOS();
	~KallumOS();

	void Tick(float elapsedTime);
	void Draw();
	void OnKeyPress(KeyPress* e);
	void OnMouseHold(MousePress* e);
	void OnMousePress(MousePress* e);

private:

	void SwitchStates();

	State* state;
};