#include "Process.h"
#include "Point.h"


Process::Process() {
	name = "";
}


Process::Process( std::string _name) {

	name = _name;

	hidden = true;
	display = false;

}

Process::Process( std::string _name, Point _position, Point _size) {

	name = _name;

	position = _position;
	size = _size;

	hidden = false;
	display = true;
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
	DrawText(name.c_str(), position.GetX() + 10 + offset.GetX(), position.GetY() + offset.GetY() + 7, 2, BLACK);


	//draws the controls
	DrawRectangle(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, RED);
	DrawRectangleLines(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, RED);

	DrawRectangle(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, GRAY);
	DrawRectangleLines(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, GRAY);
}

std::string Process::GetName() {

	return name;

}

//normalises the mouse position be relative to the window position
Point Process::NormaliseMousePos(int taskbarHeight) {

	return Point(GetMouseX() - position.GetX(), GetMouseY() - position.GetY() - taskbarHeight);
}

void Process::OnMousePress(MousePress* e, int taskbarHeight) {

	if (display) {

		CheckIfMinimizeClicked(NormaliseMousePos(taskbarHeight));
	}
}

//Checks if the minimise button was pressed and sets the display off if it was
void Process::CheckIfMinimizeClicked(Point normMousePos) {

	//checks if the mouse was within the control bar
	if (normMousePos.GetY() < barHeight) {

		if (normMousePos.GetX() > size.GetX() - buttonWidth * 2 &&
			normMousePos.GetX() < size.GetX() - buttonWidth * 1) {

			display = false;
		}
	}
}