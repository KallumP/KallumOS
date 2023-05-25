#pragma once
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <iostream>

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

	static bool CreateHardDrive() {

		//generates the file path for this instance
		std::filesystem::path osPath = std::filesystem::current_path();
		std::filesystem::path drivePath = osPath / "hardDrive";


		//checks if this path existed
		if (!std::filesystem::exists(drivePath)) {
			std::cout << "Virtual hard drive not found" << std::endl << "Creating drive now" << std::endl;

			//makes the file path
			if (!std::filesystem::create_directory(drivePath)) {
				std::cout << "Failed to create drive\n";
				return false;
			}
		}

		return true;
	}

private:
	static void SetSeed() {
		std::srand(std::time(nullptr));
	}
};