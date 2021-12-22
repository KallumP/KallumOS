#include "Process.h"


Process::Process() {

}


Process::Process(olc::PixelGameEngine* _window, std::string _name) {
	window = _window;
	name = _name;
}

void Process::Draw() {
	//std::cout << "Base process \n";

}

void Process::Tick() {

}