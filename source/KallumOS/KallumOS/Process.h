#pragma once
#include "raylib.h"

#include "Point.h"
#include "InputPress.h"

#include <iostream>

class Process {

protected:

	std::string name;
	Point position;
	Point size;

	bool hidden;
	bool display;


	int barHeight = 30; //px
	int buttonWidth = 40; //px
	void DrawBoxBar(Point offset, bool fill);
	void CheckIfMinimizeClicked(Point normMousePos);
	Point NormaliseMousePos(int taskbarHeight);



public:
	Process();
	Process( std::string _name, Point _position, Point _size);
	Process( std::string _name);

	virtual void Draw(Point offset);
	virtual void Tick() {}
	virtual std::string GetName();

	virtual void OnKeyPress(KeyPress* e) {}
	virtual void OnMousePress(MousePress* e, int taskbarHeight);

	bool GetHidden() { return hidden; }
	bool GetDisplay() { return display; }
	void ToggleDisplay() { display = !display; }
};

