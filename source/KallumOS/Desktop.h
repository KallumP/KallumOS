#pragma once
#include "raylib.h"

#include "State.h"
#include "AppLauncher.h"
#include "InputPress.h"
#include "Taskbar.h"
#include "Process.h"

#include <functional>

class Desktop : public State {

public:
	Desktop();
	//~Desktop();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);
	void OnMouseHold(MousePress* e); 
	void OnMouseRelease(MousePress* e);
	void OnMouseMove(Point* e);


private:
	
	void TaskBarClickHandle();
	void LaunchAppLauncher();
	void LaunchApp(Process* app);
	void CloseApp(Process* toClose);


	AppLauncher* launcher;
	Taskbar taskbar;
	std::vector<Process*> processes;
	Process* focused;

};

