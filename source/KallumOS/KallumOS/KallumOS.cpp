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
	controls.push_back(new TextBox(_window, Point(0.5, 0.5), Point(200, 50)));
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

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Click(mousePosition);
}

//Mouse move event
void KallumOS::MouseMove() {

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Hover(mousePosition);
}

