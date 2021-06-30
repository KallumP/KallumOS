#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Control.h"
#include "TextBox.h"

KallumOS::KallumOS() {

}

KallumOS::KallumOS(olc::PixelGameEngine* _window) {

	window = _window;
	mousePosition = new Point();
	mouseClicked = false;
	controls.push_back(new TextBox(_window, Point(0.5, 0.5), Point(250, 40)));
	controls.push_back(new TextBox(_window, Point(0.5, 0.57), Point(250, 40)));
	Focus(controls[0]);
}

KallumOS::~KallumOS() {

}

//Tick event
void KallumOS::Tick(float ElapsedTime) {

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

}

//Draw event
void KallumOS::Draw() {

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Draw();
}

//Click event
void KallumOS::Click() {

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
void KallumOS::MouseMove() {

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Hover(mousePosition);
}

//Set the focus on the input control (and unsets it from the previous)
void KallumOS::Focus(Control* toFocus) {

	//unsets the old focus (in the control) (if there was a focus already)
	if (focused != nullptr) focused->RevertFocus();

	//reverts the focus in the os
	toFocus->RevertFocus();

	//sets the focus in the new control
	focused = toFocus;
}

