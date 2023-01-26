#include "raylib.h"

#include "Input.h"
#include "KallumOS.h"
#include "InputPress.h"



Input::Input() {

	GenerateKeyPressList();
	GenerateMousePressList();
}

//generates the list of all the supported keys
void Input::GenerateKeyPressList() {

	//null input
	allKeyPressOptions.push_back(KeyPress(KEY_NULL, ""));

	//number inputs
	allKeyPressOptions.push_back(KeyPress(KEY_ZERO, "0"));
	allKeyPressOptions.push_back(KeyPress(KEY_ONE, "1"));
	allKeyPressOptions.push_back(KeyPress(KEY_TWO, "2"));
	allKeyPressOptions.push_back(KeyPress(KEY_THREE, "3"));
	allKeyPressOptions.push_back(KeyPress(KEY_FOUR, "4"));
	allKeyPressOptions.push_back(KeyPress(KEY_FIVE, "5"));
	allKeyPressOptions.push_back(KeyPress(KEY_SIX, "6"));
	allKeyPressOptions.push_back(KeyPress(KEY_SEVEN, "7"));
	allKeyPressOptions.push_back(KeyPress(KEY_EIGHT, "8"));
	allKeyPressOptions.push_back(KeyPress(KEY_NINE, "9"));

	//letter inputs
	allKeyPressOptions.push_back(KeyPress(KEY_A, "a"));
	allKeyPressOptions.push_back(KeyPress(KEY_B, "b"));
	allKeyPressOptions.push_back(KeyPress(KEY_C, "c"));
	allKeyPressOptions.push_back(KeyPress(KEY_D, "d"));
	allKeyPressOptions.push_back(KeyPress(KEY_E, "e"));
	allKeyPressOptions.push_back(KeyPress(KEY_F, "f"));
	allKeyPressOptions.push_back(KeyPress(KEY_G, "g"));
	allKeyPressOptions.push_back(KeyPress(KEY_H, "h"));
	allKeyPressOptions.push_back(KeyPress(KEY_I, "i"));
	allKeyPressOptions.push_back(KeyPress(KEY_J, "j"));
	allKeyPressOptions.push_back(KeyPress(KEY_K, "k"));
	allKeyPressOptions.push_back(KeyPress(KEY_L, "l"));
	allKeyPressOptions.push_back(KeyPress(KEY_M, "m"));
	allKeyPressOptions.push_back(KeyPress(KEY_N, "n"));
	allKeyPressOptions.push_back(KeyPress(KEY_O, "o"));
	allKeyPressOptions.push_back(KeyPress(KEY_P, "p"));
	allKeyPressOptions.push_back(KeyPress(KEY_Q, "q"));
	allKeyPressOptions.push_back(KeyPress(KEY_R, "r"));
	allKeyPressOptions.push_back(KeyPress(KEY_S, "s"));
	allKeyPressOptions.push_back(KeyPress(KEY_T, "t"));
	allKeyPressOptions.push_back(KeyPress(KEY_U, "u"));
	allKeyPressOptions.push_back(KeyPress(KEY_V, "v"));
	allKeyPressOptions.push_back(KeyPress(KEY_W, "w"));
	allKeyPressOptions.push_back(KeyPress(KEY_X, "x"));
	allKeyPressOptions.push_back(KeyPress(KEY_Y, "y"));
	allKeyPressOptions.push_back(KeyPress(KEY_Z, "z"));




	//special keys

	allKeyPressOptions.push_back(KeyPress(KEY_SPACE, " "));
	allKeyPressOptions.push_back(KeyPress(KEY_ESCAPE, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_ENTER, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_TAB, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_BACKSPACE, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_INSERT, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_DELETE, ""));

	allKeyPressOptions.push_back(KeyPress(KEY_RIGHT, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_LEFT, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_DOWN, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_UP, ""));

	allKeyPressOptions.push_back(KeyPress(KEY_PAGE_UP, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_PAGE_DOWN, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_HOME, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_END, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_CAPS_LOCK, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_SCROLL_LOCK, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_NUM_LOCK, ""));

	allKeyPressOptions.push_back(KeyPress(KEY_APOSTROPHE, "'"));
	allKeyPressOptions.push_back(KeyPress(KEY_COMMA, ","));
	allKeyPressOptions.push_back(KeyPress(KEY_MINUS, "-"));
	allKeyPressOptions.push_back(KeyPress(KEY_PERIOD, "."));
	allKeyPressOptions.push_back(KeyPress(KEY_SLASH, "/"));
	allKeyPressOptions.push_back(KeyPress(KEY_SEMICOLON, ";"));
	allKeyPressOptions.push_back(KeyPress(KEY_EQUAL, "="));

	allKeyPressOptions.push_back(KeyPress(KEY_PAUSE, ""));


	allKeyPressOptions.push_back(KeyPress(KEY_LEFT_SHIFT, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_LEFT_SHIFT, ""));




	//numpad inputs
	allKeyPressOptions.push_back(KeyPress(KEY_KP_DECIMAL, "."));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_DIVIDE, "/"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_MULTIPLY, "*"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_SUBTRACT, "-"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_ADD, "+"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_ENTER, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_EQUAL, ""));

	//number inputs (numpad)
	allKeyPressOptions.push_back(KeyPress(KEY_KP_0, "0"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_1, "1"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_2, "2"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_3, "3"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_4, "4"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_5, "5"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_6, "6"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_7, "7"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_8, "8"));
	allKeyPressOptions.push_back(KeyPress(KEY_KP_9, "9"));



	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_1, ";"));
	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_2, "/"));
	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_3, "#"));
	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_4, "["));
	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_5, "\\"));
	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_6, "]"));
	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_7, "'"));
	//allKeyPressOptions.push_back(KeyPress(KEY_OEM_8, ""));

	//function keys
	allKeyPressOptions.push_back(KeyPress(KEY_F1, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F2, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F3, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F4, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F5, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F6, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F7, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F8, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F9, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F10, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F11, ""));
	allKeyPressOptions.push_back(KeyPress(KEY_F12, ""));

}

//goes through the list of supported keys and sents the passed control the keypresses
void Input::GetKeyPress(float elapsedTime, KallumOS* caller) {

	std::vector<KeyPress*> pressedKeys;

	//KeyPress::ctrlPressed = window->GetKey(KEY_CTRL).bPressed;
	//KeyPress::shiftPressed = window->GetKey(KEY_SHIFT).bPressed;

	//loops through the delay list
	for (int i = keyPressesOnDelay.size() - 1; i >= 0; i--) {

		//checks if the current keypress from delay list was held this tick
		if (IsKeyDown(keyPressesOnDelay[i].GetKeyPress()->GetKeyCode()))

			//decays the delay timer (and checks if the delay ran out)
			if (keyPressesOnDelay[i].Decay(elapsedTime)) {

				//add this keypress into pressedKeys (it won't be duplicated because later when adding all keypresses it will check if its already in the delay list)
				pressedKeys.push_back(keyPressesOnDelay[i].GetKeyPress());

				//set the delay timer to a smaller value
				keyPressesOnDelay[i].SetFasterDelayTime();

			} else {

			}

		//if it wasn't pressed
		else

			//removes the keypress from delay list
			keyPressesOnDelay.erase(keyPressesOnDelay.begin() + i);
	}


	//loops through all the possible text key presses
	for (int i = 0; i < allKeyPressOptions.size(); i++)

		//checks if the current keypress was pressed
		if (IsKeyDown(allKeyPressOptions[i].GetKeyCode())) {

			//if the pressed key was not in the delay list
			if (!InKeyDelayList(&allKeyPressOptions[i])) {

				//add the key to the delay list
				keyPressesOnDelay.push_back(KeyDelayer(&allKeyPressOptions[i]));

				//stores the keypress
				pressedKeys.push_back(&allKeyPressOptions[i]);
			}
		}


	//calls the event method in the caller for keypress
	for (int i = 0; i < pressedKeys.size(); i++)
		caller->OnKeyPress(pressedKeys[i]);


	//separate method that does not do delays
	//this way controls can take two events delayed and not delayed, and the control objecst choose which to use

}

//returns if the passed in key was present in the delay list
bool Input::InKeyDelayList(KeyPress* key) {

	for (int i = 0; i < keyPressesOnDelay.size(); i++)
		if (keyPressesOnDelay[i].Check(key))
			return true;

	return false;
}

//populates the list of all possible mouse presses
void Input::GenerateMousePressList() {

	//adds the three mouse buttons
	for (int i = 0; i < 4; i++)
		allMousePressOptions.push_back(i);

}

//Finds all the mouse inputs and calls the corresponding event handlers
void Input::GetMouseInputs(float elapsedTime, KallumOS* caller) {

	//loops through the already registered presses
	for (int i = mousePresses.size() - 1; i >= 0; i--) {

		//checks if the current press from list was held this tick
		if (IsMouseButtonDown(mousePresses[i].GetMouseCode()))

			//calls the mouse held method
			caller->OnMouseHold(&mousePresses[i]);

		//if it wasn't pressed
		else {

			//calls the released method
			caller->OnMouseRelease(&mousePresses[i]);

			//removes the press from list
			mousePresses.erase(mousePresses.begin() + i);
		}
	}

	//loops through all the possible mouse buttons
	for (int i = 0; i < allMousePressOptions.size(); i++) {

		//checks if the current press from list was held this tick
		if (IsMouseButtonDown(allMousePressOptions[i].GetMouseCode())) {

			//checks if the press wasn't already registered
			if (!InMousePressedList(allMousePressOptions[i])) {

				//calls the mouse press method
				caller->OnMousePress(&allMousePressOptions[i]);

				//adds the press to the registered presses list
				mousePresses.push_back(allMousePressOptions[i]);
			}
		}
	}
}


//returns if the passed in key was present in the delay list
bool Input::InMousePressedList(MousePress press) {

	//loops through the list of registered presses
	for (int i = 0; i < mousePresses.size(); i++)

		//checks if the presses are the same
		if (mousePresses[i].GetMouseCode() == press.GetMouseCode())
			return true;

	return false;
}