#include "TaskManager.h"


TaskManager::TaskManager() {

}


TaskManager::TaskManager(olc::PixelGameEngine* _window, std::string _name, std::vector<Process*>* _processes, Point _position, Point _size) : Process(_window, _name, _position, _size) {

	processes = _processes;
}

void TaskManager::Draw(Point offset) {

	DrawBoxBar(offset);

	offset.Set(new Point(offset.GetX() + position.GetX() , offset.GetY() + +position.GetY() + barHeight));
	
	//process output
	//window->DrawRect(30 + offset.GetX(), 40 + offset.GetY(), 50, 50, olc::GREEN);

}