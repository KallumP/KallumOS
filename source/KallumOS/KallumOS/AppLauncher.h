#pragma once
#include "Process.h"
#include "TaskManager.h"
#include "TextEditor.h"
#include "TicTak.h"
#include "Tetris.h"

#include <vector>
#include <functional>

struct ProcessInfo {

public:
	static const int buttonPadding = 30;
	Point buttonSizes = Point(100, 50);

	std::string processName;
};

class AppLauncher : public Process {

public:
	AppLauncher();
	AppLauncher(std::vector<Process*>* _processes, Point _position, Point _size, const std::function<void(Process* toLaunch)>& _LaunchAppPointer);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);

private:
	std::vector<ProcessInfo> processInfos;
	std::vector<Process*>* processes;
	void SetupProcessInfos();

	std::function<void(Process* toLaunch)> LaunchApp;
};



