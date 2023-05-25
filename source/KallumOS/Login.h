#pragma once
#include "raylib.h"

#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"


class Login : public State {

public:
	Login(std::string _accountsFilePath);
	~Login();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);


private:
	void CheckLoginClicked();
	void CheckSwitchToCreateClicked();
	void GetAllUsers();

	void Click();
	void MouseMove();
	void ValidateLogin();
	bool ValidateCredentials(std::string _username, std::string _password, Credentials toCheck);

	Button* loginTrigger;
	Button* switchToCreateTrigger;
	TextBox* username;
	TextBox* password;

	std::string accountsFilePath;
	std::vector<Credentials> allAccounts;
};

