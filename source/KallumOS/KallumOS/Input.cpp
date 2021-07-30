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

	allKeyPressOptions.push_back(KeyPress(olc::Key::NONE, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::A, "a"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::B, "b"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::C, "c"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::D, "d"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::E, "e"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F, "f"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::G, "g"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::H, "h"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::I, "i"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::J, "j"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K, "k"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::L, "l"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::M, "m"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::N, "n"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::O, "o"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::P, "p"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::Q, "q"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::R, "r"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::S, "s"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::T, "t"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::U, "u"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::V, "v"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::W, "w"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::X, "x"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::Y, "y"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::Z, "z"));

	allKeyPressOptions.push_back(KeyPress(olc::Key::K0, "0"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K1, "1"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K2, "2"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K3, "3"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K4, "4"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K5, "5"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K6, "6"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K7, "7"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K8, "8"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::K9, "9"));

	allKeyPressOptions.push_back(KeyPress(olc::Key::NP0, "0"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP1, "1"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP2, "2"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP3, "3"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP4, "4"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP5, "5"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP6, "6"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP7, "7"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP8, "8"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP9, "9"));
	
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP_MUL, "*"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP_DIV, "/"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP_ADD, "+"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP_SUB, "-"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::NP_DECIMAL, "."));
	
	allKeyPressOptions.push_back(KeyPress(olc::Key::PERIOD, "."));
	allKeyPressOptions.push_back(KeyPress(olc::Key::EQUALS, "="));
	allKeyPressOptions.push_back(KeyPress(olc::Key::COMMA, ","));
	allKeyPressOptions.push_back(KeyPress(olc::Key::MINUS, "-"));
	
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_1, ";"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_2, "/"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_3, "#"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_4, "["));
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_5, "\\"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_6, "]"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_7, "'"));
	allKeyPressOptions.push_back(KeyPress(olc::Key::OEM_8, ""));


	allKeyPressOptions.push_back(KeyPress(olc::Key::F1, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F2, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F3, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F4, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F5, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F6, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F7, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F8, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F9, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F10, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F11, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::F12, ""));

	allKeyPressOptions.push_back(KeyPress(olc::Key::UP, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::DOWN, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::LEFT, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::RIGHT, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::SPACE, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::TAB, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::INS, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::DEL, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::HOME, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::END, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::PGUP, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::PGDN, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::BACK, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::ESCAPE, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::RETURN, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::ENTER, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::PAUSE, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::SCROLL, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::CAPS_LOCK, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::ENUM_END, ""));


	allKeyPressOptions.push_back(KeyPress(olc::Key::SHIFT, ""));
	allKeyPressOptions.push_back(KeyPress(olc::Key::CTRL, ""));
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
	for (int i = 0; i < allKeyPressOptions.size(); i++)

		//checks if the current keypress was pressed
		if (window->GetKey(allKeyPressOptions[i].GetKeyCode()).bHeld)

			//if the pressed key was not in the delay list
			if (!InDelayList(&allKeyPressOptions[i])) {

				//add the key to the delay list
				pressesOnDelay.push_back(Delayer(&allKeyPressOptions[i]));

				//stores the keypress
				pressedKeys.push_back(&allKeyPressOptions[i]);
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