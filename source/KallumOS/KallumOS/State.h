#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"
#include "KeyPress.h"

#include <vector>

enum class States { null, login, createAccount, desktop };

class State {
protected:
	olc::PixelGameEngine* window;
	std::vector<Control*> controls;

	Point* mousePosition;
	bool mouseClicked;
	Control* focused;
	States nextState;


public:

	State(olc::PixelGameEngine*);
	~State();

	virtual void Tick(float) = 0;
	virtual void Draw() = 0;

	virtual	void Click() = 0;
	virtual void MouseMove() = 0;
	virtual void OnKeyPress(KeyPress*) = 0;
	virtual States GetNextState();

	void Focus(Control*, bool);
	void NextFocus();

private:



};

