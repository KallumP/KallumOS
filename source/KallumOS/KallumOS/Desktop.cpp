#include "Desktop.h"
#include "Taskbar.h"
#include "TaskManager.h"
#include "TextEditor.h"

Desktop::Desktop() : State() {

	taskbar = Taskbar(&processes);

	Process* test;

	//test = new Process(window, "process w/ display", Point(500, 50), Point(400, 200));
	//processes.push_back(test);

	//test = new Process(window, "process w/ no display");
	//processes.push_back(test);

	TaskManager* manager = new TaskManager(&processes, Point(10, 60), Point(450, 300));
	processes.push_back(manager);

	TextEditor* editor = new TextEditor(Point(500, 50), Point(400, 200));
	processes.push_back(editor);


	taskbar.SetFocused(editor);
	focused = editor;

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

	for (int i = 0; i < processes.size(); i++)
		processes[i]->Draw(drawOffset);

	if (focused != nullptr) {
		DrawText(focused->GetName().c_str(), 10, 5, 2, BLACK);
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