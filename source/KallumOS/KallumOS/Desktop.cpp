#include "Desktop.h"
#include "Taskbar.h"
#include "TaskManager.h"
#include "TicTak.h"
#include "TextEditor.h"

Desktop::Desktop() : State() {

	taskbar = Taskbar(&processes);

	Process* test;
	Process* toFocus;

	TaskManager* manager = new TaskManager(&processes, Point(10, 60), Point(450, 300));
	processes.push_back(manager);


	TicTak* tic = new TicTak(Point(500, 50), Point(400, 200));
	processes.push_back(tic);
	toFocus = tic;

	TextEditor* editor = new TextEditor(Point(650, 350), Point(400, 200));
	processes.push_back(editor);

	taskbar.SetFocused(toFocus);
	focused = toFocus;

	backgroundColor = MAGENTA;
}

void Desktop::Tick(float) {

	//turns the window mouse values into a point
	Point* newMouse = new Point(GetMouseX(), GetMouseY());

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

			auto it = find(processes.begin(), processes.end(), focused);

			processes.erase(it);
			delete focused;
			focused = nullptr;
		}
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