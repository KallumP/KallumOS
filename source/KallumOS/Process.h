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

	bool mouseDownOnBar;


	int barHeight = 30; //px
	int buttonWidth = 40; //px
	void DrawBoxBar(Point offset, bool fill);
	void SuperMousePress(Point normMousePos);
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
	virtual void OnMouseHold(MousePress* e, int taskBarHeight);
	virtual void OnMouseRelease(MousePress* e);

	bool GetHidden() { return hidden; }
	bool GetDisplay() { return display; }
	bool GetClose() { return close; }
	void ToggleDisplay() { display = !display; }
	void UpdatePosition(Point change);

private:

	bool CheckBarClicked(Point normMousePos);
	bool CheckIfMinimizeClicked(Point normMousePos);
	bool CheckIfCloseClicked(Point normMousePos);

	Point barClickLocation;
};

