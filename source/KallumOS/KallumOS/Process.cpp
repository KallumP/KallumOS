#include "Process.h"
#include "Point.h"


Process::Process() {
	name = "";
}


Process::Process(olc::PixelGameEngine* _window, std::string _name, Point _position, Point _size) {
	window = _window;
	name = _name;

	position = _position;
	size = _size;
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
	window->FillRect(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY()  + offset.GetY(), buttonWidth, barHeight, olc::RED);
	window->DrawRect(position.GetX() + size.GetX() - buttonWidth + offset.GetX(), position.GetY()  + offset.GetY(), buttonWidth, barHeight, olc::RED);

	window->FillRect(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY()  + offset.GetY(), buttonWidth, barHeight, olc::GREY);
	window->DrawRect(position.GetX() + size.GetX() - buttonWidth * 2 + offset.GetX(), position.GetY()  + offset.GetY(), buttonWidth, barHeight, olc::GREY);
}

std::string Process::GetName() {

	return name;

}