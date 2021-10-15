#pragma once
#include "olcPixelGameEngine.h"

#include <iostream>

class Process
{

protected:
	olc::PixelGameEngine* window;
	std::string name;



public:
	Process();
	Process(olc::PixelGameEngine*, std::string);

	virtual void Draw();
};

