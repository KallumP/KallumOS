#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Control.h"
#include "TextBox.h"
#include "Login.h"

KallumOS::KallumOS(olc::PixelGameEngine* _window) {

	window = _window;
	state = new Login(_window);
}

KallumOS::~KallumOS() {

}

//Tick event
void KallumOS::Tick(float ElapsedTime) {

	state->Tick(ElapsedTime);

}

//Draw event
void KallumOS::Draw() {

	state->Draw();
}

