#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Control.h"
#include "TextBox.h"
#include "Login.h"
#include "CreateAccount.h"
#include "InputPress.h"



KallumOS::KallumOS(olc::PixelGameEngine* _window) {

	window = _window;
	state = new Login(_window);
}

KallumOS::~KallumOS() {

}

//Tick event
void KallumOS::Tick(float ElapsedTime) {

	if (state->GetNextState() != States::null)

		SwitchStates();

	else

		state->Tick(ElapsedTime);


}

//Draw event
void KallumOS::Draw() {

	state->Draw();
}


void KallumOS::OnKeyPress(KeyPress* e) {

	state->OnKeyPress(e);
}

void KallumOS::OnMouseHold(MousePress* e) {
}

void KallumOS::OnMousePress(MousePress* e) {

	state->OnMousePress(e);
}

void KallumOS::SwitchStates() {

	States toSwitch = state->GetNextState();
	delete state;

	if (toSwitch == States::login)
		state = new Login(window);
	else if (toSwitch == States::createAccount)
		state = new CreateAccount(window);
	else if (toSwitch == States::desktop)
		std::cout << "No desktop yet";

}
