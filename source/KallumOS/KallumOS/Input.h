#pragma once
#include "raylib.h"

#include "KallumOS.h"
#include "Control.h"
#include "InputPress.h" 

#include <vector>
#include <string>


struct KeyDelayer {

private:
	 float delayTime1 = 0.5f;
	 float delayTime2 = 0.05f;
	 KeyPress* key;
	float remainingTime;

public:
	KeyDelayer(KeyPress* _key) {
		key = _key;
		remainingTime = delayTime1;
	}

	bool Check(KeyPress* _key) {

		if (key == _key)
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
	Input();
	void GetKeyPress(float elapsedTime, KallumOS* caller);
	void GetMouseInputs(float elapsedTime, KallumOS* caller);

private:

	void GenerateKeyPressList();
	void GenerateMousePressList();
	bool InKeyDelayList(KeyPress* key);
	bool InMousePressedList(MousePress press);


	std::vector<KeyPress> allKeyPressOptions;
	std::vector<MousePress> allMousePressOptions;

	std::vector<KeyDelayer> keyPressesOnDelay;
	std::vector<MousePress> mousePresses;

};