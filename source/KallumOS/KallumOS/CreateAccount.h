#pragma once
#include "raylib.h"

#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"

class CreateAccount : public State {

public:
	CreateAccount(olc::PixelGameEngine*, std::string);
	~CreateAccount();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress*);
	void OnMousePress(MousePress*);



private:

	void Click();
	void MouseMove();

	void CheckCreateClicked();
	void CheckSwitchToLoginClicked();

	void GetAllUsers();
	void ValidateCredentials();
	bool UsernameExists(std::string _username);
	void SaveCredentials();

	Button* createTrigger;
	Button* switchToLoginTrigger;
	TextBox* username;
	TextBox* password;
	TextBox* password2;

	std::string accountsFilePath;
	std::vector<Credentials> allAccounts;
};

