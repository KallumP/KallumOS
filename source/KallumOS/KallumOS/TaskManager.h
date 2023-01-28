#pragma once
#include "Process.h"
#include "Point.h"

#include <vector>
#include <functional>

class TaskManager : public Process {

public:
	TaskManager();
	TaskManager(std::vector<Process*>* _processes, Point _position, Point _size);
	void BindCloseApp(const std::function<void(Process* toLaunch)>& _CloseApp) { CloseApp = _CloseApp; }


	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);

private:

	void EndTask(int indexToRemove);


	std::vector<Process*>* processes;

	int processListPadding = 30;
	int processPadding = 4;
	int processBoxHeight = 30;
	int endProcWidth = 30;

	int selected;

	std::function<void(Process* toClose)> CloseApp;
};

