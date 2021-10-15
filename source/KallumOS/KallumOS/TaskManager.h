#pragma once
#include "olcPixelGameEngine.h"
#include "Process.h"

#include <vector>

class TaskManager : public Process {

public:
	TaskManager();
	TaskManager(olc::PixelGameEngine*, std::string, std::vector<Process>*);

	void Draw();

private:
	std::vector<Process>* processes;

};

