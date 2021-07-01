#include "State.h"

#include "olcPixelGameEngine.h"
#include "State.h"
#include "Control.h"
#include "TextBox.h"

State::State(olc::PixelGameEngine* _window) {

	window = _window;
	mousePosition = new Point();
	mouseClicked = false;
}

State::~State() {

}

//Set the focus on the input control (and unsets it from the previous)
void State::Focus(Control* toFocus) {

	//unsets the old focus (in the control) (if there was a focus already)
	if (focused != nullptr) focused->InvertFocus();

	//reverts the focus in the os
	toFocus->InvertFocus();

	//sets the focus in the new control
	focused = toFocus;
}

