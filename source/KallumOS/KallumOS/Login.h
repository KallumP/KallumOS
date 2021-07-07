#pragma once
#include "olcPixelGameEngine.h"

#include "State.h"
#include "Button.h"
#include "Input.h"

class Login : public State
{

public:
	Login(olc::PixelGameEngine*, Input*);
	~Login();

	void Tick(float);
	void Draw();


private:
	void CheckLoginClicked();
	void Click();
	void MouseMove();

	Button* loginWatch;
	olc::Pixel backgroundColor;

	Input* keyboardHandler;

};

