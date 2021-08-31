#pragma once
#include "olcPixelGameEngine.h"
#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"


class CreateAccount : public State {

public:
	CreateAccount(olc::PixelGameEngine*);
	~CreateAccount();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);


private:
	void CheckCreateClicked();
	void CheckSwitchToLoginClicked();

	void Click();
	void MouseMove();
	void ValidateCredentials();

	olc::Pixel backgroundColor;

	Button* createTrigger;
	Button* switchToLoginTrigger;
	TextBox* username;
	TextBox* password;
	TextBox* password2;
};
