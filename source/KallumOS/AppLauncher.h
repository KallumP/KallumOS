#pragma once
#include "Process.h"
#include "TaskManager.h"
#include "TextEditor.h"
#include "TicTak.h"
#include "Tetris.h"
#include "Kode.h"
#include "TestWindow.h"

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
	AppLauncher(std::vector<Process*>* _processes, Point _position, Point _size);
	void BindLaunchApp(const std::function<void(Process* toLaunch)>& _LaunchApp) { LaunchApp = _LaunchApp; }
	void BindCloseApp(const std::function<void(Process* toLaunch)>& _CloseApp) { CloseApp = _CloseApp; }

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);

private:
	std::vector<ProcessInfo> processInfos;
	std::vector<Process*>* processes;
	void SetupProcessInfos();

	std::function<void(Process* toLaunch)> LaunchApp;
	std::function<void(Process* toClose)> CloseApp;
};



