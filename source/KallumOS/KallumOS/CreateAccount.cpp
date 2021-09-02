#include "CreateAccount.h"

#include "olcPixelGameEngine.h"
#include "State.h"
#include "Control.h"
#include "TextBox.h"
#include "Button.h"
#include "InputPress.h"

CreateAccount::CreateAccount(olc::PixelGameEngine* _window) : State(_window) {

	int TextboxWidth = 300;

	backgroundColor = olc::BLUE;

	username = new TextBox(_window, Point(0.5, 0.5), Point(TextboxWidth, 40), "", "Username");
	controls.push_back(username);

	password = new TextBox(_window, Point(0.5, 0.57), Point(TextboxWidth, 40), "", "Password");
	controls.push_back(password);	
	
	password2 = new TextBox(_window, Point(0.5, 0.64), Point(TextboxWidth, 40), "", "Validate password");
	controls.push_back(password2);

	createTrigger = new Button(_window, Point(0.5, 0.71), Point(TextboxWidth, 40), "Create");
	controls.push_back(createTrigger);

	switchToLoginTrigger = new Button(_window, Point(0.5, 0.78), Point(TextboxWidth, 40), "Back to Login");
	controls.push_back(switchToLoginTrigger);

	Focus(username, false);
}

CreateAccount::~CreateAccount() {

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

	if (createTrigger->GetClicked())

		ValidateCredentials();
}

void CreateAccount::ValidateCredentials() {

	if (username->GetValue() != "" &&
		password->GetValue() != "" &&
		password->GetValue() == password2->GetValue()) {

		backgroundColor = olc::GREEN;
	} else 		{
		backgroundColor = olc::RED;
	}

}
void CreateAccount::CheckSwitchToLoginClicked() {

	if (switchToLoginTrigger->GetClicked())

		nextState = States::login;
}

