#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"
#include "Point.h"
#include "Process.h"


#include <string>
#include <vector>

enum class Positions { Left, Right, Top, Bottom, Hidden };

class Taskbar : public Control
{

public:
	Taskbar();
	Taskbar(olc::PixelGameEngine*);

	void Draw();
	bool Click(Point*);
	void OnKeyPress(KeyPress*);
	Process GetClickedProcess();

private:
	Positions position;
	std::vector<Process> processes;
	Process* clickedProcess;
	Process* focusedProcess;
};

