#include "Process.h"
#include "Point.h"
#include "Helper.h"


Process::Process() {
	name = "";
	defaultFontSize = 20;
	mouseDownOnBar = false;
}


Process::Process(std::string _name) {

	name = _name;

	hidden = true;
	display = false;
	close = false;
	mouseDownOnBar = false;
	defaultFontSize = 20;

}

Process::Process(std::string _name, Point _position, Point _size) {

	name = _name;

	position = _position;
	size = _size;

	hidden = false;
	display = true;
	close = false;
	mouseDownOnBar = false;

}

void Process::Draw(Point offset) {

	if (display)

		DrawBoxBar(offset, true);
}


void Process::DrawBoxBar(Point offset, bool fill) {

	//draws the box around which the process output will be displayed

	DrawRectangleLines(position.GetX() + offset.GetX(), position.GetY() + barHeight + offset.GetY(), size.GetX(), size.GetY(), WHITE);
	if (fill)
		DrawRectangle(position.GetX() + offset.GetX(), position.GetY() + barHeight + offset.GetY(), size.GetX(), size.GetY(), WHITE);

	//draws the control bar
	DrawRectangle(position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), size.GetX(), barHeight, GRAY);
	DrawRectangleLines(position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), size.GetX(), barHeight, GRAY);

	//draws the name of the process
	DrawText(name.c_str(), position.GetX() + 10 + offset.GetX(), position.GetY() + offset.GetY() + 7, defaultFontSize, BLACK);


	//draws the controls

	//close button
	DrawRectangle(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, RED);
	DrawRectangleLines(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, RED);

	//minimise button
	DrawRectangle(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, SKYBLUE);
	DrawRectangleLines(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, SKYBLUE);
}

std::string Process::GetName() {

	return name;

}



void Process::OnMousePress(MousePress* e) {

	if (display) {

		SuperMousePress(Helper::NormaliseMousePos(position));
	}
}

void Process::SuperMousePress(Point normMousePos) {


	if (CheckBarClicked(normMousePos)) {

		if (CheckIfMinimizeClicked(normMousePos))
			return;

		if (CheckIfCloseClicked(normMousePos))
			return;

		mouseDownOnBar = true;
		barClickLocation = Point(normMousePos.GetX(), normMousePos.GetY());
	}
}

//returns if the bar was clicked on
bool Process::CheckBarClicked(Point normMousePos) {

	//checks if the mouse was within the control bar
	return normMousePos.GetY() < barHeight && normMousePos.GetY() > 0;
}

//Checks if the minimise button was pressed and sets the display off if it was
bool Process::CheckIfMinimizeClicked(Point normMousePos) {

	if (normMousePos.GetX() > size.GetX() - buttonWidth * 2 &&
		normMousePos.GetX() < size.GetX() - buttonWidth * 1) {

		display = false;
		return true;
	}

	return false;
}

//checks if the close button was pressed and sets the close flag to true
bool Process::CheckIfCloseClicked(Point normMousePos) {

	if (normMousePos.GetX() > size.GetX() - buttonWidth * 1 &&
		normMousePos.GetX() < size.GetX() - buttonWidth * 0) {

		close = true;
		return true;
	}

	return false;
}

void Process::OnMouseHold(MousePress* e) {

	if (mouseDownOnBar) {

		Point newMousePosition = Helper::NormaliseMousePos(position);

		Point mouseDifference = newMousePosition.Difference(barClickLocation);
		
		UpdatePosition(mouseDifference);
	}
}

void Process::OnMouseRelease(MousePress* e) {

	mouseDownOnBar = false;
}


void Process::UpdatePosition(Point change) {

	position.Add(change);
}