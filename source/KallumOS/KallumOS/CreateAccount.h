#pragma once
#include "olcPixelGameEngine.h"
#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"

struct Credentials {

	Credentials(std::string _username, std::string _password) {
		username = _username;
		password = _password;
	}

	std::string username;
	std::string password;
};

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

	void ReadAllUsers();
	void ValidateCredentials();
	bool UsernameExists(std::string);
	void SaveCredentials();


	olc::Pixel backgroundColor;

	Button* createTrigger;
	Button* switchToLoginTrigger;
	TextBox* username;
	TextBox* password;
	TextBox* password2;

	std::string accountsFilePath;
	std::vector<Credentials> allAccounts;
};

