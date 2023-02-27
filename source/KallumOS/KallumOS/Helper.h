#pragma once
#include <ctime>
#include <cstdlib>

static class Helper {

public:
	
	//creates a random number between (inclusivley) the start and end
	static int Random(int start, int end) {

		//should only set rand once
		if (!randSet)
			std::srand(std::time(nullptr));
		randSet = true;

		int randomNumber = std::rand() % end + start;
	}


private:

	static bool randSet = false;
};