#pragma once
#include "olcPixelGameEngine.h"

#include "State.h"
#include "Button.h"

class Login : public State
{

public:
	Login(olc::PixelGameEngine*);
	~Login();

	void Tick(float);
	void Draw();
	void Click();
	void MouseMove();


private:
	void CheckLoginClicked();

	Button* loginWatch;
	olc::Pixel backgroundColor;
};

