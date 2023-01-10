#pragma once
#include "Process.h"
#include "TaskManager.h"
#include "TextEditor.h"
#include "TicTak.h"
#include "Tetris.h"

#include <vector>

struct ProcessInfo {

public:
	static const int buttonPadding = 30;
	Point buttonSizes = Point(100, 50);

	std::string processName;
};

class AppLauncher : public Process {

public:
	AppLauncher();
	AppLauncher(std::vector<Process*>* _processes, Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);

private:
	std::vector<ProcessInfo> processInfos;
	std::vector<Process*>* processes;
	void SetupProcessInfos();

	void LaunchTetris() {
		Tetris* app = new Tetris(Point(525, 20), Point(320, 650));
		processes->push_back(app);
	}
};



