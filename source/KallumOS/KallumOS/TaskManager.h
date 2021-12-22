#pragma once
#include "olcPixelGameEngine.h"
#include "Process.h"
#include "Point.h"

#include <vector>

class TaskManager : public Process {

public:
	TaskManager();
	TaskManager(olc::PixelGameEngine*, std::string, std::vector<Process*>*, Point, Point);


	void Draw();

private:
	
	Point position;
	Point size;

	std::vector<Process*>* processes;
};

