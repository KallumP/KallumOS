#include "Login.h"
#include "raylib.h"

#include "State.h"
#include "Control.h"
#include "TextBox.h"
#include "Button.h"
#include "InputPress.h"




Login::Login(std::string _accountsFilePath) : State() {

	accountsFilePath = _accountsFilePath;

	int TextboxWidth = 300;

	backgroundColor = BLUE;

	username = new TextBox(Point(0.5, 0.5), Point(TextboxWidth, 40), "", "Username");
	controls.push_back(username);

	password = new TextBox(Point(0.5, 0.57), Point(TextboxWidth, 40), "", "Password");
	controls.push_back(password);
	password->SetObfuscation("*");

	loginTrigger = new Button(Point(0.5, 0.71), Point(TextboxWidth, 40), "Login");
	controls.push_back(loginTrigger);

	switchToCreateTrigger = new Button(Point(0.5, 0.78), Point(TextboxWidth, 40), "Create account");
	controls.push_back(switchToCreateTrigger);

	Focus(username, false);

	GetAllUsers();
}

void Login::GetAllUsers() {

	std::ifstream toRead;
	toRead.open(accountsFilePath, std::ios_base::in);

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

Login::~Login() {

}


//Tick event
void Login::Tick(float ElapsedTime) {

	//turns the window mouse values into a point
	Point* newMouse = new Point(window->GetMouseX(), window->GetMouseY());

	//checks if the new mouse is different from the old
	if (mousePosition->Different(newMouse)) {
		mousePosition->Set(newMouse);
		MouseMove();
	}

	CheckLoginClicked();
	CheckSwitchToCreateClicked();
}


//Draw event
void Login::Draw() {

	ClearBackground(backgroundColor);

	//clears all graphics on the window
	window->Clear(backgroundColor);

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Draw();
}

//Click event
void Login::Click() {

	for (int i = 0; i < (int)controls.size(); i++) {

		//checks if the control being checked was clicked
		if (controls[i]->Click(mousePosition)) {

			//sets the focus to this control
			Focus(controls[i], true);

			break;
		}
	}
}

//Mouse move event
void Login::MouseMove() {

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Hover(mousePosition);
}

//Keypress event
void Login::OnKeyPress(KeyPress* e) {

	if (e->GetKeyCode() == olc::Key::ENTER)
		if (focused != switchToCreateTrigger)
			ValidateLogin();
		else
			nextState = States::createAccount;

	else if (e->GetKeyCode() == olc::Key::TAB)
		NextFocus();
	else
		focused->OnKeyPress(e);
}

void Login::OnMousePress(MousePress* e) {

	Click();
}

void Login::CheckLoginClicked() {

	if (loginTrigger->GetClicked()) {

		//unclicks the button
		loginTrigger->InvertClicked();

		ValidateLogin();
	}
}

void Login::ValidateLogin() {

	//loops through all the user accounts
	for (int i = 0; i < allAccounts.size(); i++) {

		//checks if the credentials were good
		if (ValidateCredentials(username->GetValue(), password->GetValue(), allAccounts[i])) {

			backgroundColor = GREEN;

			nextState = States::desktop;

			break;

		} else {
			backgroundColor = RED;

		}
	}

}

bool Login::ValidateCredentials(std::string _username, std::string _password, Credentials toCheck) {

	if (toCheck.username == _username && toCheck.password == _password)
		return true;

	return false;
}

void Login::CheckSwitchToCreateClicked() {

	if (switchToCreateTrigger->GetClicked()) {

		//unclicks the button
		switchToCreateTrigger->InvertClicked();

		nextState = States::createAccount;
	}
}
