#include "TaskManager.h"


TaskManager::TaskManager() {

}


TaskManager::TaskManager(olc::PixelGameEngine* _window, std::string _name, std::vector<Process*>* _processes, Point _position, Point _size) : Process(_window, _name, _position, _size) {

	processes = _processes;
}

void TaskManager::Draw(Point offset) {

	DrawBoxBar(offset);
	offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + +position.GetY() + barHeight));


	//loops through all the processes
	for (int i = 0; i < processes->size(); i++) {


		int processBoxHeight = 30;

		//outputs a rectangle for the current process
		window->DrawRect(0 + offset.GetX(), i * processBoxHeight + offset.GetY(), size.GetX(), processBoxHeight, olc::GREEN);

		//saves the name of the curretn process
		//std::string processName = *processes[i]->GetName(); WHY DOESN'T THIS WORK
		std::vector<Process*> processesDeref = *processes;
		std::string processName = processesDeref[i]->GetName();

		//outputs the name of the process
		window->DrawString(10 + offset.GetX(), 5 + i * processBoxHeight + offset.GetY(), std::to_string(i) + ": " + processName, olc::BLACK, 2);

	}
}

void TaskManager::OnKeyPress(KeyPress* e) {

	if (e->GetKeyContent() == "x") {

		if (!processes->empty()) {


			processes->erase(processes->begin());


		}
	}
}