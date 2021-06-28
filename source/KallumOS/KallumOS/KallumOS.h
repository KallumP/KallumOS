#pragma once
#include "olcPixelGameEngine.h"
#include "Control.h"

#include <vector>

class KallumOS {

public:

	KallumOS();
	~KallumOS();

	void Tick(olc::PixelGameEngine*, float);

	void Draw(olc::PixelGameEngine*);



private:


	void Click(Point*);
	void MouseMove(Point*);

	Point* mousePosition;
	bool mouseClicked;
	std::vector<Control*> controls;



};