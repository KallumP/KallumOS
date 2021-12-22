#include "TaskManager.h"


TaskManager::TaskManager() {

}


TaskManager::TaskManager(olc::PixelGameEngine* _window, std::string _name, std::vector<Process*>* _processes, Point _position, Point _size) : Process(_window, _name) {

	processes = _processes;
	position = _position;
	size = _size;
}

void TaskManager::Draw() {
	window->DrawRect(position.GetX(), position.GetY(), size.GetX(), size.GetY() , olc::WHITE);
	//std::cout << "Task manager \n";

}