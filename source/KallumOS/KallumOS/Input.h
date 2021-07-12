#pragma once
#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Control.h"
#include "KeyPress.h" 

#include <vector>
#include <string>


struct Delayer {

private:
	float delayTime = 0.2;
	KeyPress* key;
	float remainingTime;

public:
	Delayer(KeyPress* _key) {
		key = _key;
		remainingTime = delayTime;
	}

	bool Check(KeyPress* _key) {

		if (key = _key)
			return true;
		else
			return false;
	}

	bool Hold(float elapsedTime) {

		remainingTime -= elapsedTime;

		if (remainingTime > 0)
			return false;
		else
			return true;
	}

};

class Input {

public:
	Input(olc::PixelGameEngine*);
	void GetKeyPress(float, KallumOS*);

private:

	void GenerateKeyPressList();
	bool InHistory(KeyPress* key);

	olc::PixelGameEngine* window;

	std::vector<KeyPress> textPresses;
	std::vector<KeyPress> modifierPresses;
	std::vector<KeyPress> specialPresses;

	std::vector<Delayer> pressesOnDelay;

};



class MousePress {

};