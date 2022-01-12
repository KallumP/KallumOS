#pragma once
#include "olcPixelGameEngine.h"
#include "Process.h"
#include "Point.h"

#include <vector>

class TaskManager : public Process {

public:
	TaskManager();
	TaskManager(olc::PixelGameEngine*, std::string, std::vector<Process*>*, Point, Point);


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
};

