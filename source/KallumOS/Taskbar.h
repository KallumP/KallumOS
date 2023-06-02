#pragma once
#include "raylib.h"

#include "Control.h"
#include "Point.h"
#include "Process.h"


#include <string>
#include <vector>

enum class Positions { Left, Right, Top, Bottom, Hidden };

class Taskbar : public Control {

public:
	int height;


	Taskbar();
	Taskbar(std::vector<Process*>* _processes);

	void Draw();
	bool Click(Point* mousePosition);
	void OnKeyPress(KeyPress* e) {}

	Process* GetClickedProcess();
	void SetFocused(Process* toSet);

private:
	Positions position;
	std::vector<Process*>* processes;
	Process* clickedProcess;
	Process* focusedProcess;

	void HandleClickedProcess();
};

