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

	void CloseApp(Process* toClose);

private:

	void Click() {};
	void MouseMove();
	
	void TaskBarClickHandle();
	void LaunchApp(Process* app);


	AppLauncher* launcher;
	Taskbar taskbar;
	std::vector<Process*> processes;
	Process* focused;

};

