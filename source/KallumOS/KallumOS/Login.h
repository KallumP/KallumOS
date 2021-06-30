#pragma once
#include "State.h"

class Login : public State
{

public:
	Login(olc::PixelGameEngine*);
	~Login();

	void Tick(float);
	void Draw();
	void Click();
	void MouseMove();


private:

};

