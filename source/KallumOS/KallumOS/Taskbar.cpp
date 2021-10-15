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

	int height = 50;
	window->FillRect(0, 0, window->ScreenWidth(), height, olc::CYAN);

	for (int i = 0; i < processes.size(); i++)
		window->DrawRect(height * i, 0, height, height, olc::BLACK);
}

bool Taskbar::Click(Point*) {
	return false;
}
void Taskbar::OnKeyPress(KeyPress*) {
}
Process Taskbar::GetClickedProcess() {
	return Process();
}

void Taskbar::TakeNewProcess(Process* toTake) {

	processes.push_back(toTake);

}