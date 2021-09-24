#include "Taskbar.h"

Taskbar::Taskbar() {

}

Taskbar::Taskbar(olc::PixelGameEngine* _window) : Control(_window, Point(), Point()) { 

	clickedProcess = nullptr;
	focusedProcess = nullptr;
	position = Positions::Top;
	focused = false;

}

void Taskbar::Draw() { 

	window->FillRect(0, 0, window->ScreenWidth(), 10, olc::CYAN);

}
bool Taskbar::Click(Point*) {
	return false;
}
void Taskbar::OnKeyPress(KeyPress*) { 
}
Process Taskbar::GetClickedProcess() { 
	return Process();
}