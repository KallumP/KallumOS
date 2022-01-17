#include "Desktop.h"
#include "Taskbar.h"
#include "TaskManager.h"

Desktop::Desktop(olc::PixelGameEngine* _window) : State(_window) {

	taskbar = Taskbar(_window, &processes);

	Process* test;

	test = new Process(window, "process w/ display", Point(500, 50), Point(400, 200));
	processes.push_back(test);

	test = new Process(window, "process w/ no display");
	processes.push_back(test);

	TaskManager* manager = new TaskManager(window, &processes, Point(10, 60), Point(450, 300));
	processes.push_back(manager);

	taskbar.SetFocused(manager);
	focused = manager;

	backgroundColor = olc::DARK_MAGENTA;
}

void Desktop::Tick(float) {

	//turns the window mouse values into a point
	Point* newMouse = new Point(window->GetMouseX(), window->GetMouseY());

	//checks if the new mouse is different from the old
	if (mousePosition->Different(newMouse)) {
		mousePosition->Set(newMouse);
		MouseMove();
	}

	if (focused != nullptr) {

	}
}

void Desktop::Draw() {

	//clears all graphics on the window
	window->Clear(backgroundColor);

	taskbar.Draw();
	Point drawOffset = Point(0, taskbar.height);

	for (int i = 0; i < processes.size(); i++)
		processes[i]->Draw(drawOffset);

	if (focused != nullptr) {
		window->DrawString(10, 5 + taskbar.height, "Focused: " + focused->GetName(), olc::BLACK, 2);
	}

}

void Desktop::OnKeyPress(KeyPress* e) {

	for (int i = 0; i < processes.size(); i++)
		processes[i]->OnKeyPress(e);

}

void Desktop::OnMousePress(MousePress* e) {

	//passes the click event to the taskbar
	if (taskbar.Click(mousePosition))
		TaskBarClickHandle();


	if (focused != nullptr) {

		focused->OnMousePress(e, taskbar.height);

		bool focusToDisplay = focused->GetDisplay();

		if (!focused->GetDisplay()) {

			focused = nullptr;
			taskbar.SetFocused(nullptr);
		}
	}


	//loop through the other non focus processes
	//for (int i = 0; i < processes.size(); i++)
	//	processes[i]->OnMousePress(e, taskbar.height);

}

void Desktop::MouseMove() {



}

void Desktop::TaskBarClickHandle() {

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