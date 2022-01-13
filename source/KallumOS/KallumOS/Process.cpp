#include "Process.h"
#include "Point.h"


Process::Process() {
	name = "";
}


Process::Process(olc::PixelGameEngine* _window, std::string _name) {

	window = _window;
	name = _name;

	hidden = true;
	display = false;

}

Process::Process(olc::PixelGameEngine* _window, std::string _name, Point _position, Point _size) {
	window = _window;
	name = _name;

	position = _position;
	size = _size;

	hidden = false;
	display = true;
}

void Process::Draw(Point offset) {

	if (display)

		DrawBoxBar(offset);
}


void Process::DrawBoxBar(Point offset) {

	//draws the box around which the process output will be displayed
	window->DrawRect(position.GetX() + offset.GetX(), position.GetY() + barHeight + offset.GetY(), size.GetX(), size.GetY(), olc::WHITE);

	//draws the control bar
	window->FillRect(position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), size.GetX(), barHeight, olc::WHITE);
	window->DrawRect(position.GetX() + offset.GetX(), position.GetY() + offset.GetY(), size.GetX(), barHeight, olc::WHITE);

	//draws the name of the process
	window->DrawString(position.GetX() + 10 + offset.GetX(), position.GetY() + offset.GetY() + 7, name, olc::BLACK, 2);


	//draws the controls
	window->FillRect(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, olc::RED);
	window->DrawRect(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, olc::RED);

	window->FillRect(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, olc::GREY);
	window->DrawRect(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY() + offset.GetY(), buttonWidth, barHeight, olc::GREY);
}

std::string Process::GetName() {

	return name;

}

//normalises the mouse position be relative to the window position
Point Process::NormaliseMousePos(int taskbarHeight) {

	return Point(window->GetMouseX() - position.GetX(), window->GetMouseY() - position.GetY() - taskbarHeight);
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