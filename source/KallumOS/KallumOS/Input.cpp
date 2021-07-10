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

	textPresses.push_back(KeyPress(olc::Key::K0, ""));
	textPresses.push_back(KeyPress(olc::Key::K1, ""));
	textPresses.push_back(KeyPress(olc::Key::K2, ""));
	textPresses.push_back(KeyPress(olc::Key::K3, ""));
	textPresses.push_back(KeyPress(olc::Key::K4, ""));
	textPresses.push_back(KeyPress(olc::Key::K5, ""));
	textPresses.push_back(KeyPress(olc::Key::K6, ""));
	textPresses.push_back(KeyPress(olc::Key::K7, ""));
	textPresses.push_back(KeyPress(olc::Key::K8, ""));
	textPresses.push_back(KeyPress(olc::Key::K9, ""));

	textPresses.push_back(KeyPress(olc::Key::NP0, ""));
	textPresses.push_back(KeyPress(olc::Key::NP1, ""));
	textPresses.push_back(KeyPress(olc::Key::NP2, ""));
	textPresses.push_back(KeyPress(olc::Key::NP3, ""));
	textPresses.push_back(KeyPress(olc::Key::NP4, ""));
	textPresses.push_back(KeyPress(olc::Key::NP5, ""));
	textPresses.push_back(KeyPress(olc::Key::NP6, ""));
	textPresses.push_back(KeyPress(olc::Key::NP7, ""));
	textPresses.push_back(KeyPress(olc::Key::NP8, ""));
	textPresses.push_back(KeyPress(olc::Key::NP9, ""));

	textPresses.push_back(KeyPress(olc::Key::NP_MUL, ""));
	textPresses.push_back(KeyPress(olc::Key::NP_DIV, ""));
	textPresses.push_back(KeyPress(olc::Key::NP_ADD, ""));
	textPresses.push_back(KeyPress(olc::Key::NP_SUB, ""));
	textPresses.push_back(KeyPress(olc::Key::NP_DECIMAL, ""));
	textPresses.push_back(KeyPress(olc::Key::PERIOD, ""));

	textPresses.push_back(KeyPress(olc::Key::EQUALS, ""));
	textPresses.push_back(KeyPress(olc::Key::COMMA, ""));
	textPresses.push_back(KeyPress(olc::Key::MINUS, ""));


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

	specialPresses.push_back(KeyPress(olc::Key::OEM_1, ""));
	specialPresses.push_back(KeyPress(olc::Key::OEM_2, ""));
	specialPresses.push_back(KeyPress(olc::Key::OEM_3, ""));
	specialPresses.push_back(KeyPress(olc::Key::OEM_4, ""));
	specialPresses.push_back(KeyPress(olc::Key::OEM_5, ""));
	specialPresses.push_back(KeyPress(olc::Key::OEM_6, ""));
	specialPresses.push_back(KeyPress(olc::Key::OEM_7, ""));
	specialPresses.push_back(KeyPress(olc::Key::OEM_8, ""));
	specialPresses.push_back(KeyPress(olc::Key::CAPS_LOCK, ""));
	specialPresses.push_back(KeyPress(olc::Key::ENUM_END, ""));


	modifierPresses.push_back(KeyPress(olc::Key::SHIFT, ""));
	modifierPresses.push_back(KeyPress(olc::Key::CTRL, ""));
}

//goes through the list of supported keys and sents the passed control the keypresses
void Input::GetKeyPress(KallumOS* caller) {

	std::vector<KeyPress*> pressedKeys;

	KeyPress::ctrlPressed == window->GetKey(olc::Key::CTRL).bPressed;
	KeyPress::shiftPressed == window->GetKey(olc::Key::SHIFT).bPressed;


	for (int i = 0; i < textPresses.size(); i++)

		if (window->GetKey(textPresses[i].GetKeyCode()).bPressed || window->GetKey(textPresses[i].GetKeyCode()).bHeld)

			pressedKeys.push_back(&textPresses[i]);


	for (int i = 0; i < pressedKeys.size(); i++)

		caller->OnKeyPress(pressedKeys[i]);

}