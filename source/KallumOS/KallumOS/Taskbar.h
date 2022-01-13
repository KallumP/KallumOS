#pragma once
#include "olcPixelGameEngine.h"
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
	Taskbar(olc::PixelGameEngine* _window, std::vector<Process*>* _processes);

	void Draw();
	bool Click(Point*);
	void OnKeyPress(KeyPress*) {}

	Process* GetClickedProcess();
	void SetFocused(Process* toSet);

private:
	Positions position;
	std::vector<Process*>* processes;
	Process* clickedProcess;
	Process* focusedProcess;

	void HandleClickedProcess();
};

