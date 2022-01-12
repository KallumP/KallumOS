#include "TaskManager.h"


TaskManager::TaskManager() {

}


TaskManager::TaskManager(olc::PixelGameEngine* _window, std::string _name, std::vector<Process*>* _processes, Point _position, Point _size) : Process(_window, _name, _position, _size) {

	processes = _processes;
}

void TaskManager::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));


		offset.Set(new Point(offset.GetX(), offset.GetY() + processListPadding));

		//loops through all the processes
		for (int i = 0; i < processes->size(); i++) {

			offset.Set(new Point(offset.GetX(), offset.GetY() + processPadding));


			//outputs a rectangle for the current process
			window->DrawRect(0 + offset.GetX(), i * processBoxHeight + offset.GetY(), size.GetX(), processBoxHeight, olc::GREEN);

			if (selected == i)
				window->FillRect(0 + offset.GetX(), i * processBoxHeight + offset.GetY(), size.GetX(), processBoxHeight, olc::GREEN);

			//saves the name of the curretn process
			//std::string processName = *processes[i]->GetName(); WHY DOESN'T THIS WORK
			std::vector<Process*> processesDeref = *processes;
			std::string processName = processesDeref[i]->GetName();

			//outputs the name of the process
			window->DrawString(10 + offset.GetX(), 5 + i * processBoxHeight + offset.GetY(), std::to_string(i) + ": " + processName, olc::BLACK, 2);

			//draws the end process button
			window->DrawRect(size.GetX() - endProcWidth + offset.GetX(), i * processBoxHeight + offset.GetY(), endProcWidth, processBoxHeight, olc::RED);
			window->FillRect(size.GetX() - endProcWidth + offset.GetX(), i * processBoxHeight + offset.GetY(), endProcWidth, processBoxHeight, olc::RED);
		}
	}
}

void TaskManager::OnKeyPress(KeyPress* e) {

	if (e->GetKeyContent() == "x")

		if (!processes->empty())

			EndTask(selected);
}


void TaskManager::OnMousePress(MousePress* e, int taskbarHeight) {

	int checkOffset;

	//saves the height of the mouse
	Point normalisedMouse = Point(window->GetMouseX() - position.GetX(), window->GetMouseY() - position.GetY() - taskbarHeight);

	//loops through all the processes
	for (int i = 0; i < processes->size(); i++) {

		//offset of the box bar, list padding and the padding between each process
		checkOffset = barHeight + processListPadding + processPadding * (i + 1) + processBoxHeight * i;

		//checks if the mouse y was within one of the process squares
		if (normalisedMouse.GetY() > checkOffset && normalisedMouse.GetY() < checkOffset + processBoxHeight)

			//checks if the mouse x was within the end task button
			if (normalisedMouse.GetX() > size.GetX() - endProcWidth && normalisedMouse.GetX() < size.GetX())
				EndTask(i);
			else
				selected = i;
	}

}

//takes an index of a task to end
void TaskManager::EndTask(int indexToRemove) {


	processes->erase(processes->begin() + indexToRemove);
}