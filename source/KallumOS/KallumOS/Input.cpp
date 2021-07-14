#include "Input.h"
#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "KeyPress.h"



Input::Input(olc::PixelGameEngine* _window) {
	window = _window;
	GenerateKeyPressList();
}



//generates the list of all the supported keys
void Input::GenerateKeyPressList() {

	//textPresses.push_back(KeyPress(olc::Key::NONE, ""));
	textPresses.push_back(KeyPress(olc::Key::A, "a"));
	textPresses.push_back(KeyPress(olc::Key::B, "b"));
	textPresses.push_back(KeyPress(olc::Key::C, "c"));
	textPresses.push_back(KeyPress(olc::Key::D, "d"));
	textPresses.push_back(KeyPress(olc::Key::E, "e"));
	textPresses.push_back(KeyPress(olc::Key::F, "f"));
	textPresses.push_back(KeyPress(olc::Key::G, "g"));
	textPresses.push_back(KeyPress(olc::Key::H, "h"));
	textPresses.push_back(KeyPress(olc::Key::I, "i"));
	textPresses.push_back(KeyPress(olc::Key::J, "j"));
	textPresses.push_back(KeyPress(olc::Key::K, "k"));
	textPresses.push_back(KeyPress(olc::Key::L, "l"));
	textPresses.push_back(KeyPress(olc::Key::M, "m"));
	textPresses.push_back(KeyPress(olc::Key::N, "n"));
	textPresses.push_back(KeyPress(olc::Key::O, "o"));
	textPresses.push_back(KeyPress(olc::Key::P, "p"));
	textPresses.push_back(KeyPress(olc::Key::Q, "q"));
	textPresses.push_back(KeyPress(olc::Key::R, "r"));
	textPresses.push_back(KeyPress(olc::Key::S, "s"));
	textPresses.push_back(KeyPress(olc::Key::T, "t"));
	textPresses.push_back(KeyPress(olc::Key::U, "u"));
	textPresses.push_back(KeyPress(olc::Key::V, "v"));
	textPresses.push_back(KeyPress(olc::Key::W, "w"));
	textPresses.push_back(KeyPress(olc::Key::X, "x"));
	textPresses.push_back(KeyPress(olc::Key::Y, "y"));
	textPresses.push_back(KeyPress(olc::Key::Z, "z"));

	textPresses.push_back(KeyPress(olc::Key::K0, "0"));
	textPresses.push_back(KeyPress(olc::Key::K1, "1"));
	textPresses.push_back(KeyPress(olc::Key::K2, "2"));
	textPresses.push_back(KeyPress(olc::Key::K3, "3"));
	textPresses.push_back(KeyPress(olc::Key::K4, "4"));
	textPresses.push_back(KeyPress(olc::Key::K5, "5"));
	textPresses.push_back(KeyPress(olc::Key::K6, "6"));
	textPresses.push_back(KeyPress(olc::Key::K7, "7"));
	textPresses.push_back(KeyPress(olc::Key::K8, "8"));
	textPresses.push_back(KeyPress(olc::Key::K9, "9"));

	textPresses.push_back(KeyPress(olc::Key::NP0, "0"));
	textPresses.push_back(KeyPress(olc::Key::NP1, "1"));
	textPresses.push_back(KeyPress(olc::Key::NP2, "2"));
	textPresses.push_back(KeyPress(olc::Key::NP3, "3"));
	textPresses.push_back(KeyPress(olc::Key::NP4, "4"));
	textPresses.push_back(KeyPress(olc::Key::NP5, "5"));
	textPresses.push_back(KeyPress(olc::Key::NP6, "6"));
	textPresses.push_back(KeyPress(olc::Key::NP7, "7"));
	textPresses.push_back(KeyPress(olc::Key::NP8, "8"));
	textPresses.push_back(KeyPress(olc::Key::NP9, "9"));

	textPresses.push_back(KeyPress(olc::Key::NP_MUL, "*"));
	textPresses.push_back(KeyPress(olc::Key::NP_DIV, "/"));
	textPresses.push_back(KeyPress(olc::Key::NP_ADD, "+"));
	textPresses.push_back(KeyPress(olc::Key::NP_SUB, "-"));
	textPresses.push_back(KeyPress(olc::Key::NP_DECIMAL, "."));

	textPresses.push_back(KeyPress(olc::Key::PERIOD, "."));
	textPresses.push_back(KeyPress(olc::Key::EQUALS, "="));
	textPresses.push_back(KeyPress(olc::Key::COMMA, ","));
	textPresses.push_back(KeyPress(olc::Key::MINUS, "-"));

	textPresses.push_back(KeyPress(olc::Key::OEM_1, ";"));
	textPresses.push_back(KeyPress(olc::Key::OEM_2, "/"));
	textPresses.push_back(KeyPress(olc::Key::OEM_3, "#"));
	textPresses.push_back(KeyPress(olc::Key::OEM_4, "["));
	textPresses.push_back(KeyPress(olc::Key::OEM_5, "\\"));
	textPresses.push_back(KeyPress(olc::Key::OEM_6, "]"));
	textPresses.push_back(KeyPress(olc::Key::OEM_7, "'"));
	textPresses.push_back(KeyPress(olc::Key::OEM_8, ""));

	specialPresses.push_back(KeyPress(olc::Key::F1, ""));
	specialPresses.push_back(KeyPress(olc::Key::F2, ""));
	specialPresses.push_back(KeyPress(olc::Key::F3, ""));
	specialPresses.push_back(KeyPress(olc::Key::F4, ""));
	specialPresses.push_back(KeyPress(olc::Key::F5, ""));
	specialPresses.push_back(KeyPress(olc::Key::F6, ""));
	specialPresses.push_back(KeyPress(olc::Key::F7, ""));
	specialPresses.push_back(KeyPress(olc::Key::F8, ""));
	specialPresses.push_back(KeyPress(olc::Key::F9, ""));
	specialPresses.push_back(KeyPress(olc::Key::F10, ""));
	specialPresses.push_back(KeyPress(olc::Key::F11, ""));
	specialPresses.push_back(KeyPress(olc::Key::F12, ""));

	specialPresses.push_back(KeyPress(olc::Key::UP, ""));
	specialPresses.push_back(KeyPress(olc::Key::DOWN, ""));
	specialPresses.push_back(KeyPress(olc::Key::LEFT, ""));
	specialPresses.push_back(KeyPress(olc::Key::RIGHT, ""));
	specialPresses.push_back(KeyPress(olc::Key::SPACE, ""));
	specialPresses.push_back(KeyPress(olc::Key::TAB, ""));
	specialPresses.push_back(KeyPress(olc::Key::INS, ""));
	specialPresses.push_back(KeyPress(olc::Key::DEL, ""));
	specialPresses.push_back(KeyPress(olc::Key::HOME, ""));
	specialPresses.push_back(KeyPress(olc::Key::END, ""));
	specialPresses.push_back(KeyPress(olc::Key::PGUP, ""));
	specialPresses.push_back(KeyPress(olc::Key::PGDN, ""));
	specialPresses.push_back(KeyPress(olc::Key::BACK, ""));
	specialPresses.push_back(KeyPress(olc::Key::ESCAPE, ""));
	specialPresses.push_back(KeyPress(olc::Key::RETURN, ""));
	specialPresses.push_back(KeyPress(olc::Key::ENTER, ""));
	specialPresses.push_back(KeyPress(olc::Key::PAUSE, ""));
	specialPresses.push_back(KeyPress(olc::Key::SCROLL, ""));

	specialPresses.push_back(KeyPress(olc::Key::CAPS_LOCK, ""));
	specialPresses.push_back(KeyPress(olc::Key::ENUM_END, ""));


	modifierPresses.push_back(KeyPress(olc::Key::SHIFT, ""));
	modifierPresses.push_back(KeyPress(olc::Key::CTRL, ""));
}

//goes through the list of supported keys and sents the passed control the keypresses
void Input::GetKeyPress(float elapsedTime, KallumOS* caller) {

	std::vector<KeyPress*> pressedKeys;

	//KeyPress::ctrlPressed = window->GetKey(olc::Key::CTRL).bPressed;
	//KeyPress::shiftPressed = window->GetKey(olc::Key::SHIFT).bPressed;

	//loops through the delay list
	for (int i = pressesOnDelay.size() - 1; i >= 0; i--) {

		//checks if the current keypress from delay list was not held this tick
		if (window->GetKey(pressesOnDelay[i].GetKeyPress()->GetKeyCode()).bHeld)

			//decays the delay timer (and checks if the delay ran out)
			if (pressesOnDelay[i].Decay(elapsedTime)) {

				//add this keypress into pressedKeys (it won't be duplicated because later when adding all keypresses it will check if its already in the delay list)
				pressedKeys.push_back(pressesOnDelay[i].GetKeyPress());

				//set the delay timer to a smaller value
				pressesOnDelay[i].SetFasterDelayTime();

			} else {

			}

		//if it wasn't pressed
		else

			//removes the keypress from delay list
			pressesOnDelay.erase(pressesOnDelay.begin() + i);
	}


	//loops through all the possible text key presses
	for (int i = 0; i < textPresses.size(); i++)

		//checks if the current keypress was pressed
		if (window->GetKey(textPresses[i].GetKeyCode()).bHeld)

			//if the pressed key was not in the delay list
			if (!InDelayList(&textPresses[i])) {

				//add the key to the delay list
				pressesOnDelay.push_back(Delayer(&textPresses[i]));

				//stores the keypress
				pressedKeys.push_back(&textPresses[i]);
			}



	//loops through all the possible special key presses
	for (int i = 0; i < specialPresses.size(); i++)

		//checks if the current keypress was pressed
		if (window->GetKey(specialPresses[i].GetKeyCode()).bHeld)

			//if the pressed key was not in the delay list
			if (!InDelayList(&specialPresses[i])) {

				//add the key to the delay list
				pressesOnDelay.push_back(Delayer(&specialPresses[i]));

				//stores the keypress
				pressedKeys.push_back(&specialPresses[i]);
			}


	//calls the event method in the caller for keypress
	for (int i = 0; i < pressedKeys.size(); i++)
		caller->OnKeyPress(pressedKeys[i]);


	//separate method that does not do delays
//this way controls can take two events delayed and not delayed, these controls choose which to use

}

bool Input::InDelayList(KeyPress* key) {

	for (int i = 0; i < pressesOnDelay.size(); i++)
		if (pressesOnDelay[i].Check(key))
			return true;

	return false;
}