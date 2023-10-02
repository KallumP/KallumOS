#include "raylib.h"
#include "CreateAccount.h"

#include "State.h"
#include "Control.h"
#include "TextBox.h"
#include "Button.h"
#include "InputPress.h"

#include <iostream>
#include <fstream>

CreateAccount::CreateAccount(std::string _accountsFilePath) : State() {

	accountsFilePath = _accountsFilePath;

	int TextboxWidth = 300;

	backgroundColor = BLUE;

	username = new TextBox(Point(0.5, 0.5), Point(TextboxWidth, 40), "", "Username");
	controls.push_back(username);

	password = new TextBox(Point(0.5, 0.57), Point(TextboxWidth, 40), "", "Password");
	controls.push_back(password);
	password->SetObfuscation("*");

	password2 = new TextBox(Point(0.5, 0.64), Point(TextboxWidth, 40), "", "Validate password");
	controls.push_back(password2);
	password2->SetObfuscation("*");

	createTrigger = new Button(Point(0.5, 0.71), Point(TextboxWidth, 40), "Create");
	controls.push_back(createTrigger);

	switchToLoginTrigger = new Button(Point(0.5, 0.78), Point(TextboxWidth, 40), "Back to Login");
	controls.push_back(switchToLoginTrigger);

	Focus(username, false);

	GetAllUsers();
}

CreateAccount::~CreateAccount() {

}

void CreateAccount::GetAllUsers() {

	std::ifstream toRead;
	toRead.open(accountsFilePath);

	while (toRead.good()) {

		std::string fileUsername;
		std::getline(toRead, fileUsername);
		//std::cout << fileUsername << std::endl;

		std::string filePassword;
		std::getline(toRead, filePassword);
		//std::cout << filePassword << std::endl;

		allAccounts.push_back(Credentials(fileUsername, filePassword));
	}

	toRead.close();

}

void CreateAccount::Tick(float elapsedTime) {

	CheckCreateClicked();
	CheckSwitchToLoginClicked();
}

void CreateAccount::Draw() {

	//clears all graphics on the window
	ClearBackground(backgroundColor);

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Draw();
}

void CreateAccount::OnMouseMove(Point* e) {
	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->OnMouseMove(e);
}

void CreateAccount::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == KEY_ENTER)
		if (focused != switchToLoginTrigger)
			ValidateCredentials();
		else
			nextState = States::login;

	else if (e->GetKeyCode() == KEY_TAB)
		NextFocus();
	else
		focused->OnKeyPress(e);
}

void CreateAccount::OnMousePress(MousePress* e) {

	//loops through all of the controls
	for (int i = 0; i < (int)controls.size(); i++) {

		//checks if the control being checked was clicked
		if (controls[i]->OnMousePress(e)) {

			//sets the focus to this control
			Focus(controls[i], true);

			break;
		}
	}
}

void CreateAccount::CheckCreateClicked() {

	if (createTrigger->GetClicked()) {

		//unclicks the button
		createTrigger->InvertClicked();

		ValidateCredentials();
	}

}

void CreateAccount::ValidateCredentials() {

	//checks if the credentials are not empty, passwords match and the username is not taken
	if (username->GetValue() != "" &&
		password->GetValue() != "" &&
		password->GetValue() == password2->GetValue() &&
		!UsernameExists(username->GetValue())) {

		SaveCredentials();
		backgroundColor = GREEN;
	} else {
		backgroundColor = RED;
	}
}

bool CreateAccount::UsernameExists(std::string _username) {

	//loops through all the accounts
	for (int i = 0; i < allAccounts.size(); i++)

		//checks if the usernames are the same
		if (allAccounts[i].username == _username)

			return true;

	return false;
}

void CreateAccount::SaveCredentials() {

	std::ofstream toWrite;
	toWrite.open(accountsFilePath, std::ios_base::app);

	toWrite << username->GetValue() << std::endl;
	toWrite << password->GetValue() << std::endl;

	toWrite.close();
}

void CreateAccount::CheckSwitchToLoginClicked() {

	if (switchToLoginTrigger->GetClicked()) {

		//unclicks the button
		switchToLoginTrigger->InvertClicked();

		nextState = States::login;
	}
}
