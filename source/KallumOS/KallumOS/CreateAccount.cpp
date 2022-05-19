#include "raylib.h"
#include "CreateAccount.h"

#include "State.h"
#include "Control.h"
#include "TextBox.h"
#include "Button.h"
#include "InputPress.h"

CreateAccount::CreateAccount(olc::PixelGameEngine* _window, std::string _accountsFilePath) : State(_window) {

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
	toRead.open(accountsFilePath, std::ios_base::in);

	while (toRead.good()) {

		std::string fileUsername;
		std::getline(toRead, fileUsername);
		std::cout << fileUsername << std::endl;

		std::string filePassword;
		std::getline(toRead, filePassword);
		std::cout << filePassword << std::endl;

		allAccounts.push_back(Credentials(fileUsername, filePassword));
	}

	toRead.close();

}

void CreateAccount::Tick(float) {

	//turns the window mouse values into a point
	Point* newMouse = new Point(window->GetMouseX(), window->GetMouseY());

	//checks if the new mouse is different from the old
	if (mousePosition->Different(newMouse)) {
		mousePosition->Set(newMouse);
		MouseMove();
	}

	CheckCreateClicked();
	CheckSwitchToLoginClicked();
}

void CreateAccount::Draw() {

	//clears all graphics on the window
	window->Clear(backgroundColor);

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Draw();
}

void CreateAccount::Click() {

	//loops through all of the controls
	for (int i = 0; i < (int)controls.size(); i++) {

		//checks if the control being checked was clicked
		if (controls[i]->Click(mousePosition)) {

			//sets the focus to this control
			Focus(controls[i], true);

			break;
		}
	}
}

void CreateAccount::MouseMove() {
	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Hover(mousePosition);
}

void CreateAccount::OnKeyPress(KeyPress* e) {
	if (e->GetKeyCode() == olc::Key::ENTER)
		if (focused != switchToLoginTrigger)
			ValidateCredentials();
		else
			nextState = States::login;

	else if (e->GetKeyCode() == olc::Key::TAB)
		NextFocus();
	else
		focused->OnKeyPress(e);
}

void CreateAccount::OnMousePress(MousePress* e) {

	Click();
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
	}
	else {
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
