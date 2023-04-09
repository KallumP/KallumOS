#pragma once
#include <ctime>
#include <cstdlib>

class Helper {

public:
	
	static void SetupHelper() {
		SetSeed();
	}

	//creates a random number between (inclusivley) the start and end
	static int Random(int start, int end) {
		
		//shifts the random number up by one if the end is 0
		int shift = 0;
		if (end == 0)
			shift = 1;
		end += shift;
		start += shift;

		int randomNumber = std::rand() % end + start;
		return randomNumber - shift;
	}

private:
	static void SetSeed() {
		std::srand(std::time(nullptr));
	}
};