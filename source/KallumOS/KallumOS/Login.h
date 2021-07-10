#pragma once
#include "olcPixelGameEngine.h"
#include "State.h"
#include "Button.h"
#include "KeyPress.h"


class Login : public State
{

public:
	Login(olc::PixelGameEngine*);
	~Login();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);


private:
	void CheckLoginClicked();
	void Click();
	void MouseMove();

	Button* loginWatch;
	olc::Pixel backgroundColor;
};

