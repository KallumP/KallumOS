#pragma once
#include "olcPixelGameEngine.h"
#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"


class Login : public State {

public:
	Login(olc::PixelGameEngine*);
	~Login();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);
	void OnMousePress(MousePress*);


private:
	void CheckLoginClicked();
	void CheckSwitchToCreateClicked();

	void Click();
	void MouseMove();
	void ValidateLogin();

	olc::Pixel backgroundColor;

	Button* loginTrigger;
	Button* switchToCreateTrigger;
	TextBox* username;
	TextBox* password;
};

