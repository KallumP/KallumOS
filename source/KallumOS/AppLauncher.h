#pragma once
#include "Process.h"
#include "TaskManager.h"
#include "TextEditor.h"
#include "TicTak.h"
#include "Tetris.h"
#include "Kode.h"
#include "TestWindow.h"

#include "Button.h"

#include <vector>
#include <functional>

struct ProcessInfo {

public:
	static inline int buttonPadding = 30;
	static inline Point buttonSizes = Point(100, 50);

	std::string processName;
	std::function<void()> launchCode;

	ProcessInfo(std::string _processName, std::function<void()> _launchCode) {
		processName = _processName;
		launchCode = _launchCode;
	}
};

class AppLauncher : public Process {

public:
	AppLauncher();
	AppLauncher(std::vector<Process*>* _processes, Point _position, Point _size);
	void BindLaunchApp(const std::function<void(Process* toLaunch)>& _LaunchApp) { LaunchApp = _LaunchApp; }
	void BindCloseApp(const std::function<void(Process* toLaunch)>& _CloseApp) { CloseApp = _CloseApp; }

	void Tick(float elapsedTime);
	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);

private:
	std::vector<ProcessInfo> processInfos;
	std::vector<Process*>* processes;
	void SetupProcessInfos();
	void HandleButtonClicks();

	std::function<void(Process* toLaunch)> LaunchApp;
	std::function<void(Process* toClose)> CloseApp;

	Button scrollUp;
	Button scrollDown;
	int displayStart;
};



