#pragma once
#include "olcPixelGameEngine.h"
#include "Process.h"
#include "Point.h"

#include <vector>

class IPFetch : public Process {



public:
	IPFetch();
	IPFetch(olc::PixelGameEngine* _window, Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);

private:
	
	void FetchIP();

	std::string hostName;
	std::string hostAddress;
};

