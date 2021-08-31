#include "State.h"

#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"

State::State(olc::PixelGameEngine* _window) {

	window = _window;
	mousePosition = new Point();
	mouseClicked = false;
	nextState = States::null;
}

State::~State() {

}

//Set the focus on the input control (and unsets it from the previous)
void State::Focus(Control* toFocus, bool click) {

	//unsets the old focus (in the control) (if there was a focus already)
	if (focused != nullptr) 
		focused->InvertFocus(click);

	//reverts the focus in the os
	toFocus->InvertFocus(click);

	//sets the focus in the new control
	focused = toFocus;
}

void State::NextFocus() {

	//loops through all controls in this state
	for (int i = 0; i < controls.size(); i++) {

		//checks if the current focus is this one
		if (controls[i] == focused) {

			//checks if the next focus doesn't go out of array bounds
			if (i + 1 < controls.size())

				Focus(controls[i + 1], false);

			else
				Focus(controls[0], false);

			return;
		}
	}
}


States State::GetNextState() {

	return nextState;
}
