#include "Taskbar.h"

Taskbar::Taskbar() {

}

Taskbar::Taskbar(olc::PixelGameEngine* _window, std::vector<Process*>* _processes) : Control(_window, Point(), Point()) {

	clickedProcess = nullptr;
	focusedProcess = nullptr;
	position = Positions::Top;
	focused = false;

	height = 50;

	processes = _processes;

}

void Taskbar::Draw() {

	window->FillRect(0, 0, window->ScreenWidth(), height, olc::CYAN);

	int nonHiddenIndex = 0;

	//loops through all processes
	for (int i = 0; i < processes->size(); i++) {

		//stores the list of derefferenced processes
		std::vector<Process*> processesDeref = *processes;

		//checks if the current process should be displayed
		if (!processesDeref[i]->GetHidden()) {

			//draws a square for the current process
			window->DrawRect(height * nonHiddenIndex, 0, height, height, olc::BLACK);

			if (processesDeref[i] == focusedProcess) {
				window->FillRect(height * nonHiddenIndex, 0, height, height, olc::BLUE);
			}

			//draws the index of the current process
			window->DrawString(nonHiddenIndex * height + 10, height / 2, std::to_string(i), olc::BLACK, 2);

			nonHiddenIndex++;
		}
	}
}

bool Taskbar::Click(Point*) {

	if (window->GetMouseY() < height) {

		HandleClickedProcess();

		return true;
	}
	return false;
}


void Taskbar::HandleClickedProcess() {

	int mouseX = window->GetMouseX();

	int nonHiddenIndex = 0;

	//loops through all processes
	for (int i = 0; i < processes->size(); i++) {

		//stores the list of derefferenced processes
		std::vector<Process*> processesDeref = *processes;

		//checks if the current process should be displayed
		if (!processesDeref[i]->GetHidden()) {

			//checks if the current process' icon was clicked
			if (mouseX > height * nonHiddenIndex && mouseX < height * (nonHiddenIndex + 1)) {

				SetFocused(processesDeref[i]);
				clickedProcess = processesDeref[i];

				break;
			}
			
			nonHiddenIndex++;
		}
	}
}

Process* Taskbar::GetClickedProcess() {
	return clickedProcess;
}

void Taskbar::SetFocused(Process* toSet) {

	focusedProcess = toSet;
}
