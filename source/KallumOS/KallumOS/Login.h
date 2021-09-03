#pragma once
#include "olcPixelGameEngine.h"
#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"


class Login : public State {

public:
	Login(olc::PixelGameEngine*, std::string);
	~Login();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);
	void OnMousePress(MousePress*);


private:
	void CheckLoginClicked();
	void CheckSwitchToCreateClicked();
	void GetAllUsers();

	void Click();
	void MouseMove();
	void ValidateLogin();
	bool ValidateCredentials(std::string, std::string, Credentials);

	olc::Pixel backgroundColor;

	Button* loginTrigger;
	Button* switchToCreateTrigger;
	TextBox* username;
	TextBox* password;

	std::string accountsFilePath;
	std::vector<Credentials> allAccounts;
};

