#pragma once
#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Control.h"
#include "KeyPress.h" 

#include <vector>
#include <string>


struct Delayer {

private:
	 float delayTime1 = 0.45;
	 float delayTime2 = 0.05;
	KeyPress* key;
	float remainingTime;

public:
	Delayer(KeyPress* _key) {
		key = _key;
		remainingTime = delayTime1;
	}

	bool Check(KeyPress* _key) {

		if (key = _key)
			return true;
		else
			return false;
	}

	bool Decay(float elapsedTime) {

		remainingTime -= elapsedTime;

		if (remainingTime > 0)
			return false;
		else
			return true;
	}

	KeyPress* GetKeyPress() {
		return key;
	}

	void SetNewDelayTime(float newDelay) {
		remainingTime = newDelay;
	}

	void SetFasterDelayTime() {
		remainingTime = delayTime2;
	}

};

class Input {

public:
	Input(olc::PixelGameEngine*);
	void GetKeyPress(float, KallumOS*);

private:

	void GenerateKeyPressList();
	bool InDelayList(KeyPress* key);

	olc::PixelGameEngine* window;

	std::vector<KeyPress> textPresses;
	std::vector<KeyPress> modifierPresses;
	std::vector<KeyPress> specialPresses;

	std::vector<Delayer> pressesOnDelay;

};



class MousePress {

};