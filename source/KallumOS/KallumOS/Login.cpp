#include "Login.h"

#include "olcPixelGameEngine.h"
#include "State.h"
#include "Control.h"
#include "TextBox.h"
#include "Button.h"
#include "KeyPress.h"



Login::Login(olc::PixelGameEngine* _window) : State(_window) {

	backgroundColor = olc::BLUE;

	username = new TextBox(_window, Point(0.5, 0.5), Point(250, 40), "user1");
	controls.push_back(username);

	password = new TextBox(_window, Point(0.5, 0.57), Point(250, 40), "pass");
	controls.push_back(password);

	loginTrigger = new Button(_window, Point(0.5, 0.64), Point(250, 40), "Login");
	controls.push_back(loginTrigger);

	Focus(username);
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

	//if the user has held the right mouse button
	if (window->GetMouse(0).bHeld) {

		//checks if the os thinks the mouse has already been clicked 
		if (!mouseClicked) {

			mouseClicked = true;
			Click();
		} else {

			//no need to do anything if the mouse was already clicked down
		}
	} else
		mouseClicked = false;

	CheckLoginClicked();
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
			Focus(controls[i]);

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
		ValidateLogin();
	else
		focused->OnKeyPress(e);
}

void Login::CheckLoginClicked() {

	if (loginTrigger->GetClicked())

		ValidateLogin();
}


void Login::ValidateLogin() {

	//checks if the credentials were good
	if (username->GetValue() == "user1" && password->GetValue() == "pass")

		backgroundColor = olc::GREEN;

	else
		backgroundColor = olc::RED;


	loginTrigger->InvertClicked();


}
