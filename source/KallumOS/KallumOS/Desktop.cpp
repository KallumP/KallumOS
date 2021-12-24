#include "Desktop.h"
#include "Taskbar.h"
#include "TaskManager.h"


Desktop::Desktop(olc::PixelGameEngine* _window) : State(_window) {


	taskbar = Taskbar(_window);

	Process* test = new Process(window, "based", Point(), Point());
	processes.push_back(test);
	taskbar.TakeNewProcess(test);

	TaskManager* manager = new TaskManager(window, "Manager", &processes, Point(10,10), Point(450,300));
	processes.push_back(manager);
	taskbar.TakeNewProcess(manager);

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

}

void Desktop::Draw() {
	//clears all graphics on the window
	window->Clear(backgroundColor);


	taskbar.Draw();
	Point drawOffset = Point(0, taskbar.height);


	for (int i = 0; i < processes.size(); i++) 
		processes[i]->Draw(drawOffset);
	
}

void Desktop::OnKeyPress(KeyPress*) {
	backgroundColor = olc::DARK_GREY;
}

void Desktop::OnMousePress(MousePress* e) {
	Click();
}



void Desktop::Click() {

	//passes the click event to the taskbar
	if (taskbar.Click(mousePosition)) {

	}
}
void Desktop::MouseMove() {

}