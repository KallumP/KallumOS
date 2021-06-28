#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Control.h"
#include "TextBox.h"

KallumOS::KallumOS() {

	mousePosition = new Point();
	mouseClicked = false;
	controls.push_back(new TextBox(Point(500, 500), Point(200, 50)));
}

KallumOS::~KallumOS() {

}

//Tick event
void KallumOS::Tick(olc::PixelGameEngine* window, float ElapsedTime) {

	Point* newMouse = new Point(window->GetMouseX(), window->GetMouseY());

	//checks if the new mouse is different from the old
	if (mousePosition->Different(newMouse)) {
		mousePosition->Set(newMouse);
		MouseMove(mousePosition);
	}


	//if the user has clicked the mouse
	if (window->GetMouse(0).bHeld) {

		if (!mouseClicked) {
			mouseClicked = true;
			Click(newMouse);
		}

	} else {
		mouseClicked = false;
	}

}

//Draw event
void KallumOS::Draw(olc::PixelGameEngine* window) {

	Control* control;

	for (int i = 0; i < (int)controls.size(); i++) {

		control = controls[i];

		control->Draw(window);
	}
}

//Click event
void KallumOS::Click(Point* position) {

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Click(mousePosition);
	

	std::cout << "clicked | ";
}

//Mouse move event
void KallumOS::MouseMove(Point* position) {

	for (int i = 0; i < (int)controls.size(); i++)
		controls[i]->Hover(mousePosition);

	std::cout << "moved | ";
}

