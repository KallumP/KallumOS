#include "raylib.h"

#include "KallumOS.h"
#include "Control.h"
#include "TextBox.h"
#include "Login.h"
#include "CreateAccount.h"
#include "InputPress.h"
#include "Desktop.h"



KallumOS::KallumOS() {

	state = new Login("accounts");
}

KallumOS::~KallumOS() {

}

//Tick event
void KallumOS::Tick(float elapsedTime) {

	if (state->GetNextState() != States::null)
		SwitchStates();

	else
		state->Tick(elapsedTime);
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

	if (toSwitch == States::login)
		state = new Login(window, "accounts");
	else if (toSwitch == States::createAccount)
		state = new CreateAccount(window, "accounts");
	else if (toSwitch == States::desktop)
		state = new Desktop(window);
}
