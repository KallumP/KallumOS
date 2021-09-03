#include "Login.h"

#include "olcPixelGameEngine.h"
#include "State.h"
#include "Control.h"
#include "TextBox.h"
#include "Button.h"
#include "InputPress.h"



Login::Login(olc::PixelGameEngine* _window, std::string _accountsFilePath) : State(_window) {

	accountsFilePath = _accountsFilePath;

	int TextboxWidth = 300;

	backgroundColor = olc::BLUE;

	username = new TextBox(_window, Point(0.5, 0.5), Point(TextboxWidth, 40), "", "Username");
	controls.push_back(username);

	password = new TextBox(_window, Point(0.5, 0.57), Point(TextboxWidth, 40), "", "Password");
	controls.push_back(password);

	loginTrigger = new Button(_window, Point(0.5, 0.71), Point(TextboxWidth, 40), "Login");
	controls.push_back(loginTrigger);

	switchToCreateTrigger = new Button(_window, Point(0.5, 0.78), Point(TextboxWidth, 40), "Create account");
	controls.push_back(switchToCreateTrigger);

	Focus(username, false);
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

	//checks if the credentials were good
	if (username->GetValue() == "user1" && password->GetValue() == "pass") {

		backgroundColor = olc::GREEN;

		//nextState = States::desktop;

	} else {
		backgroundColor = olc::RED;

	}
	loginTrigger->InvertClicked();

}

void Login::CheckSwitchToCreateClicked() {

	if (switchToCreateTrigger->GetClicked()) {

		//unclicks the button
		switchToCreateTrigger->InvertClicked();

		nextState = States::createAccount;
	}
}
