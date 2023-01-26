#include "Desktop.h"
#include "Taskbar.h"

Desktop::Desktop() : State() {

	taskbar = Taskbar(&processes);

	OpenLauncher();

	backgroundColor = VIOLET;
}

void Desktop::Tick(float elapsedTime) {

	//turns the window mouse values into a point
	Point* newMouse = new Point(GetMouseX(), GetMouseY());

	//checks if the new mouse is different from the old
	if (mousePosition->Different(newMouse)) {
		mousePosition->Set(newMouse);
		MouseMove();
	}

	if (focused != nullptr) {
		focused->Tick(elapsedTime);
	}
}

void Desktop::Draw() {

	//clears all graphics on the window
	ClearBackground(backgroundColor);

	taskbar.Draw();
	Point drawOffset = Point(0, taskbar.height);

	if (focused != nullptr) {
		DrawText(focused->GetName().c_str(), 10, drawOffset.GetY() + 5, 2, BLACK);
	}

	for (int i = 0; i < processes.size(); i++)
		processes[i]->Draw(drawOffset);
}

void Desktop::OnKeyPress(KeyPress* e) {

	if (focused == nullptr)
		if (e->GetKeyCode() == KEY_A)
			OpenLauncher();

	//if there was a focused window
	if (focused != nullptr)
		if (focused->GetDisplay())
			focused->OnKeyPress(e);
}

void Desktop::OnMousePress(MousePress* e) {

	//passes the click event to the taskbar
	if (taskbar.Click(mousePosition))
		TaskBarClickHandle();

	//if there was a focused window
	if (focused != nullptr) {

		//send the click to the focused process
		focused->OnMousePress(e, taskbar.height);

		//checks if the process is no longer displayed
		if (!focused->GetDisplay()) {

			focused = nullptr;
			taskbar.SetFocused(nullptr);


			//checks if the process should close
		} else if (focused->GetClose()) {

			CloseApp(focused);
		}
	}
}

void Desktop::OnMouseHold(MousePress* e) {

	//if there was a focused window
	if (focused != nullptr) {

		//send the click to the focused process
		focused->OnMouseHold(e, taskbar.height);
	}
}

void Desktop::OnMouseRelease(MousePress* e) {

	//if there was a focused window
	if (focused != nullptr) {

		//send the click to the focused process
		focused->OnMouseRelease(e);
	}
}

void Desktop::MouseMove() {



}

void Desktop::TaskBarClickHandle() {

	//checks if an empty space was clicked on the task bar
	if (taskbar.GetClickedProcess() != nullptr) {

		//checks if the clicked icon was the focused process
		if (focused == taskbar.GetClickedProcess()) {

			//sets to process to stop display
			focused->ToggleDisplay();

			//unfocuses the process
			focused = nullptr;
			taskbar.SetFocused(nullptr);

		} else {

			focused = taskbar.GetClickedProcess();

			//checks if the process was not being displayed
			if (!taskbar.GetClickedProcess()->GetDisplay())

				focused->ToggleDisplay();
		}
	}
}

void Desktop::OpenLauncher() {

	launcher = new AppLauncher(&processes, Point(10, 50), Point(160, 400));
	processes.push_back(launcher);
	taskbar.SetFocused(launcher);
	focused = launcher;
}

void Desktop::CloseApp(Process* toclose) {

	auto it = find(processes.begin(), processes.end(), toclose);

	if (toclose == launcher)
		launcher = nullptr;

	processes.erase(it);
	delete focused;
	focused = nullptr;
}