#pragma once
#include "raylib.h"

#include "State.h"
#include "Button.h"
#include "InputPress.h"
#include "TextBox.h"
#include "Taskbar.h"

class Desktop : public State {

public:
	Desktop();
	//~Desktop();

	void Tick(float);
	void Draw();
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e);


private:

	void Click() {};
	void MouseMove();
	
	void TaskBarClickHandle();
	//void StartProcess();



	Taskbar taskbar;
	std::vector<Process*> processes;
	Process* focused;

};

