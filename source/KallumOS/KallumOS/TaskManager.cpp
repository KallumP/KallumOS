#include "TaskManager.h"


TaskManager::TaskManager() {



}


TaskManager::TaskManager(olc::PixelGameEngine* _window, std::string _name, std::vector<Process>* _processes) : Process(_window, _name) {

	processes = _processes;

}

void TaskManager::Draw() {
	window->DrawRect(200, 200, 100, 100, olc::WHITE);


}