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

	allKeyPresses.push_back(KeyPress(olc::Key::NONE, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::A, "a"));
	allKeyPresses.push_back(KeyPress(olc::Key::B, "b"));
	allKeyPresses.push_back(KeyPress(olc::Key::C, "c"));
	allKeyPresses.push_back(KeyPress(olc::Key::D, "d"));
	allKeyPresses.push_back(KeyPress(olc::Key::E, "e"));
	allKeyPresses.push_back(KeyPress(olc::Key::F, "f"));
	allKeyPresses.push_back(KeyPress(olc::Key::G, "g"));
	allKeyPresses.push_back(KeyPress(olc::Key::H, "h"));
	allKeyPresses.push_back(KeyPress(olc::Key::I, "i"));
	allKeyPresses.push_back(KeyPress(olc::Key::J, "j"));
	allKeyPresses.push_back(KeyPress(olc::Key::K, "k"));
	allKeyPresses.push_back(KeyPress(olc::Key::L, "l"));
	allKeyPresses.push_back(KeyPress(olc::Key::M, "m"));
	allKeyPresses.push_back(KeyPress(olc::Key::N, "n"));
	allKeyPresses.push_back(KeyPress(olc::Key::O, "o"));
	allKeyPresses.push_back(KeyPress(olc::Key::P, "p"));
	allKeyPresses.push_back(KeyPress(olc::Key::Q, "q"));
	allKeyPresses.push_back(KeyPress(olc::Key::R, "r"));
	allKeyPresses.push_back(KeyPress(olc::Key::S, "s"));
	allKeyPresses.push_back(KeyPress(olc::Key::T, "t"));
	allKeyPresses.push_back(KeyPress(olc::Key::U, "u"));
	allKeyPresses.push_back(KeyPress(olc::Key::V, "v"));
	allKeyPresses.push_back(KeyPress(olc::Key::W, "w"));
	allKeyPresses.push_back(KeyPress(olc::Key::X, "x"));
	allKeyPresses.push_back(KeyPress(olc::Key::Y, "y"));
	allKeyPresses.push_back(KeyPress(olc::Key::Z, "z"));

	allKeyPresses.push_back(KeyPress(olc::Key::K0, "0"));
	allKeyPresses.push_back(KeyPress(olc::Key::K1, "1"));
	allKeyPresses.push_back(KeyPress(olc::Key::K2, "2"));
	allKeyPresses.push_back(KeyPress(olc::Key::K3, "3"));
	allKeyPresses.push_back(KeyPress(olc::Key::K4, "4"));
	allKeyPresses.push_back(KeyPress(olc::Key::K5, "5"));
	allKeyPresses.push_back(KeyPress(olc::Key::K6, "6"));
	allKeyPresses.push_back(KeyPress(olc::Key::K7, "7"));
	allKeyPresses.push_back(KeyPress(olc::Key::K8, "8"));
	allKeyPresses.push_back(KeyPress(olc::Key::K9, "9"));

	allKeyPresses.push_back(KeyPress(olc::Key::NP0, "0"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP1, "1"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP2, "2"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP3, "3"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP4, "4"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP5, "5"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP6, "6"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP7, "7"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP8, "8"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP9, "9"));
	
	allKeyPresses.push_back(KeyPress(olc::Key::NP_MUL, "*"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP_DIV, "/"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP_ADD, "+"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP_SUB, "-"));
	allKeyPresses.push_back(KeyPress(olc::Key::NP_DECIMAL, "."));
	
	allKeyPresses.push_back(KeyPress(olc::Key::PERIOD, "."));
	allKeyPresses.push_back(KeyPress(olc::Key::EQUALS, "="));
	allKeyPresses.push_back(KeyPress(olc::Key::COMMA, ","));
	allKeyPresses.push_back(KeyPress(olc::Key::MINUS, "-"));
	
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_1, ";"));
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_2, "/"));
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_3, "#"));
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_4, "["));
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_5, "\\"));
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_6, "]"));
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_7, "'"));
	allKeyPresses.push_back(KeyPress(olc::Key::OEM_8, ""));


	allKeyPresses.push_back(KeyPress(olc::Key::F1, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F2, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F3, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F4, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F5, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F6, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F7, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F8, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F9, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F10, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F11, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::F12, ""));

	allKeyPresses.push_back(KeyPress(olc::Key::UP, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::DOWN, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::LEFT, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::RIGHT, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::SPACE, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::TAB, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::INS, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::DEL, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::HOME, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::END, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::PGUP, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::PGDN, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::BACK, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::ESCAPE, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::RETURN, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::ENTER, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::PAUSE, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::SCROLL, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::CAPS_LOCK, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::ENUM_END, ""));


	allKeyPresses.push_back(KeyPress(olc::Key::SHIFT, ""));
	allKeyPresses.push_back(KeyPress(olc::Key::CTRL, ""));
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
	for (int i = 0; i < allKeyPresses.size(); i++)

		//checks if the current keypress was pressed
		if (window->GetKey(allKeyPresses[i].GetKeyCode()).bHeld)

			//if the pressed key was not in the delay list
			if (!InDelayList(&allKeyPresses[i])) {

				//add the key to the delay list
				pressesOnDelay.push_back(Delayer(&allKeyPresses[i]));

				//stores the keypress
				pressedKeys.push_back(&allKeyPresses[i]);
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