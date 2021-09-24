#include "Desktop.h"
#include "Taskbar.h"


Desktop::Desktop(olc::PixelGameEngine* _window) : State(_window) {
	
	taskbar = Taskbar(_window);

	backgroundColor = olc::DARK_MAGENTA;
}

void Desktop::Tick(float) {

}
void Desktop::Draw() {
	//clears all graphics on the window
	window->Clear(backgroundColor);
	taskbar.Draw();
}
void Desktop::OnKeyPress(KeyPress*) {
	backgroundColor = olc::DARK_GREY;
}
void Desktop::OnMousePress(MousePress*) {

}



void Desktop::Click() {

}
void Desktop::MouseMove() {

}