#include "olcPixelGameEngine.h"
#include "Input.h"

Input::Input() {
	GenerateKeyList();
}

//generates the list of all the supported keys
void Input::GenerateKeyList() {

	allKeys = {
		olc::Key::NONE,
		olc::Key::A,
		olc::Key::B,
		olc::Key::C,
		olc::Key::D,
		olc::Key::E,
		olc::Key::F,
		olc::Key::G,
		olc::Key::H,
		olc::Key::I,
		olc::Key::J,
		olc::Key::K,
		olc::Key::L,
		olc::Key::M,
		olc::Key::N,
		olc::Key::O,
		olc::Key::P,
		olc::Key::Q,
		olc::Key::R,
		olc::Key::S,
		olc::Key::T,
		olc::Key::U,
		olc::Key::V,
		olc::Key::W,
		olc::Key::X,
		olc::Key::Y,
		olc::Key::Z,

		olc::Key::K0,
		olc::Key::K1,
		olc::Key::K2,
		olc::Key::K3,
		olc::Key::K4,
		olc::Key::K5,
		olc::Key::K6,
		olc::Key::K7,
		olc::Key::K8,
		olc::Key::K9,

		olc::Key::F1,
		olc::Key::F2,
		olc::Key::F3,
		olc::Key::F4,
		olc::Key::F5,
		olc::Key::F6,
		olc::Key::F7,
		olc::Key::F8,
		olc::Key::F9,
		olc::Key::F10,
		olc::Key::F11,
		olc::Key::F12,

		olc::Key::UP,
		olc::Key::DOWN,
		olc::Key::LEFT,
		olc::Key::RIGHT,
		olc::Key::SPACE,
		olc::Key::TAB,
		olc::Key::SHIFT,
		olc::Key::CTRL,
		olc::Key::INS,
		olc::Key::DEL,
		olc::Key::HOME,
		olc::Key::END,
		olc::Key::PGUP,
		olc::Key::PGDN,
		olc::Key::BACK,
		olc::Key::ESCAPE,
		olc::Key::RETURN,
		olc::Key::ENTER,
		olc::Key::PAUSE,
		olc::Key::SCROLL,

		olc::Key::NP0,
		olc::Key::NP1,
		olc::Key::NP2,
		olc::Key::NP3,
		olc::Key::NP4,
		olc::Key::NP5,
		olc::Key::NP6,
		olc::Key::NP7,
		olc::Key::NP8,
		olc::Key::NP9,

		olc::Key::NP_MUL,
		olc::Key::NP_DIV,
		olc::Key::NP_ADD,
		olc::Key::NP_SUB,
		olc::Key::NP_DECIMAL,
		olc::Key::PERIOD,

		olc::Key::EQUALS,
		olc::Key::COMMA,
		olc::Key::MINUS,

		olc::Key::OEM_1,
		olc::Key::OEM_2,
		olc::Key::OEM_3,
		olc::Key::OEM_4,
		olc::Key::OEM_5,
		olc::Key::OEM_6,
		olc::Key::OEM_7,
		olc::Key::OEM_8,
		olc::Key::CAPS_LOCK,
		olc::Key::ENUM_END };

}

//goes through the list of supported keys and sents the passed control the keypresses
void Input::GetKeyPress(olc::PixelGameEngine* window, Control* control) {

	std::vector<olc::Key> pressedKeys;

	if (allKeys.size() != 0) {

		for (int i = 0; i < allKeys.size(); i++)
			if (window->GetKey(allKeys[i]).bPressed || window->GetKey(allKeys[i]).bHeld)
				pressedKeys.push_back(allKeys[i]);

		control->KeyboardInput(pressedKeys);
	}
}