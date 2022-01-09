#pragma once
#include "olcPixelGameEngine.h"
#include "Point.h"
#include "InputPress.h"

#include <iostream>

class Process
{

protected:
	olc::PixelGameEngine* window;
	std::string name;
	Point position;
	Point size;


	int barHeight = 30; //px
	int buttonWidth = 40; //px
	void DrawBoxBar(Point offset);

public:
	Process();
	Process(olc::PixelGameEngine* _window, std::string _name, Point _position, Point _size);

	virtual void Draw(Point offset) {}
	virtual void Tick() {}
	virtual std::string GetName();

	virtual void OnKeyPress(KeyPress* e) {}
	virtual void OnMousePress(MousePress* e) {}
	
};

