#include "Taskbar.h"

Taskbar::Taskbar() {

}

Taskbar::Taskbar(std::vector<Process*>* _processes) : Control(Point(), Point()) {

	clickedProcess = nullptr;
	focusedProcess = nullptr;
	position = Positions::Top;
	focused = false;

	height = 50;

	processes = _processes;

}

void Taskbar::Draw() {

	DrawRectangle(0, 0, GetScreenWidth(), height, SKYBLUE);

	int nonHiddenIndex = 0;

	//loops through all processes
	for (int i = 0; i < processes->size(); i++) {

		//stores the list of derefferenced processes
		std::vector<Process*> processesDeref = *processes;

		//checks if the current process should be displayed
		if (!processesDeref[i]->GetHidden()) {

			if (processesDeref[i] == focusedProcess) 
				DrawRectangle(height * nonHiddenIndex, 0, height, height, BLUE);

			//draws a square for the current process
			DrawRectangleLines(height * nonHiddenIndex, 0, height, height, BLACK);

			
			//draws the index of the current process
			DrawText(std::to_string(i).c_str(), nonHiddenIndex * height + 10, height / 2, 2, BLACK);

			nonHiddenIndex++;
		}
	}
}

bool Taskbar::Click(Point* mousePosition) {

	if (GetMouseY() < height) {

		HandleClickedProcess();

		return true;
	}
	return false;
}


void Taskbar::HandleClickedProcess() {

	int mouseX = GetMouseX();

	int nonHiddenIndex = 0;

	//loops through all processes
	for (int i = 0; i < processes->size(); i++) {

		//checks if the current process should be displayed in the task manager
		if (!(*processes)[i]->GetHidden()) {

			//checks if the current process' icon was clicked
			if (mouseX > height * nonHiddenIndex && mouseX < height * (nonHiddenIndex + 1)) {

				SetFocused((*processes)[i]);
				clickedProcess = (*processes)[i];

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
