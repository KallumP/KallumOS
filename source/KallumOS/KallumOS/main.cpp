#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "KallumOS.h"
#include "Input.h"
#include "KeyPress.h"


class PixelGameEngine : public olc::PixelGameEngine {
public:
	PixelGameEngine() {
		sAppName = "KallumOS";
	}

	bool OnUserCreate() override {

		os = new KallumOS(this);
		intputHandler = new Input(this);
		frameRate = 60;
		targetFrameTime = 1 / frameRate;
		timeSinceLastFrame = targetFrameTime;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		//keeps track of how much time has passed
		runtime += fElapsedTime;
		timeSinceLastFrame += fElapsedTime;

		intputHandler->GetKeyPress(fElapsedTime, os);
		

		//checks to see if enough time has passed since the last frame
		if (timeSinceLastFrame >= targetFrameTime) {

			//resets the time since last frame
			timeSinceLastFrame = 0;

			os->Tick(fElapsedTime);
			os->Draw();
		}

		//debug
		//DrawString(10, 10, std::to_string(runtime), olc::BLACK, 1);

		return true;
	}

private:

	KallumOS* os;
	Input* intputHandler;
	float frameRate;
	float targetFrameTime;
	float timeSinceLastFrame;
	float runtime;
};

int main() {

	PixelGameEngine* window = new PixelGameEngine();

	if (window->Construct(1000, 700, 1, 1))
		window->Start();

	return 0;
}
