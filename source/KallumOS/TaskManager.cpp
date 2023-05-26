#include "TaskManager.h"


TaskManager::TaskManager() {

}


TaskManager::TaskManager(std::vector<Process*>* _processes, Point _position, Point _size) : Process("Task manager", _position, _size) {

	processes = _processes;
}

void TaskManager::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));


		offset.Set(new Point(offset.GetX(), offset.GetY() + processListPadding));

		//loops through all the processes
		for (int i = 0; i < processes->size(); i++) {

			offset.Set(new Point(offset.GetX(), offset.GetY() + processPadding));

			//outputs a rectangle for the current process
			DrawRectangleLines(0 + offset.GetX(), i * processBoxHeight + offset.GetY(), size.GetX(), processBoxHeight, GREEN);

			if (selected == i)
				DrawRectangle(0 + offset.GetX(), i * processBoxHeight + offset.GetY(), size.GetX(), processBoxHeight, GREEN);

			//saves the name of the curretn process
			std::string processName = (*processes)[i]->GetName();

			//outputs the name of the process
			std::string processNameBuffer = std::to_string(i) + ": " + processName;
			DrawText(processNameBuffer.c_str(), 10 + offset.GetX(), 5 + i * processBoxHeight + offset.GetY(), defaultFontSize, BLACK);

			//draws the end process button
			DrawRectangleLines(size.GetX() - endProcWidth + offset.GetX(), i * processBoxHeight + offset.GetY(), endProcWidth, processBoxHeight, RED);
			DrawRectangle(size.GetX() - endProcWidth + offset.GetX(), i * processBoxHeight + offset.GetY(), endProcWidth, processBoxHeight, RED);
		}
	}
}

void TaskManager::OnKeyPress(KeyPress* e) {

	if (display) {

	}
}


void TaskManager::OnMousePress(MousePress* e) {

	if (display) {

		SuperMousePress(NormaliseMousePos());

		int checkOffset;

		//saves the height of the mouse
		Point normalisedMouse = NormaliseMousePos();

		//loops through all the processes
		for (int i = processes->size() - 1; i >= 0; i--) {

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
}

//takes an index of a task to end
void TaskManager::EndTask(int indexToRemove) {

	Process* toRemove;
	toRemove = (*processes)[indexToRemove];
	CloseApp(toRemove);
}