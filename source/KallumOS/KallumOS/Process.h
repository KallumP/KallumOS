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

	int defaultFontSize;

	bool hidden;
	bool display;
	bool close;


	int barHeight = 30; //px
	int buttonWidth = 40; //px
	void DrawBoxBar(Point offset, bool fill);
	void CheckBarButtonsClicked(Point normMousePos);
	void CheckIfMinimizeClicked(Point normMousePos);
	void CheckIfCloseClicked(Point normMousePos);
	Point NormaliseMousePos(int yOffSet);



public:
	Process();
	Process( std::string _name, Point _position, Point _size);
	Process( std::string _name);

	virtual void Draw(Point offset);
	virtual void Tick(float elapsedTime) {}
	virtual std::string GetName();

	virtual void OnKeyPress(KeyPress* e) {}
	virtual void OnMousePress(MousePress* e, int taskbarHeight);

	bool GetHidden() { return hidden; }
	bool GetDisplay() { return display; }
	bool GetClose() { return close; }
	void ToggleDisplay() { display = !display; }
};

