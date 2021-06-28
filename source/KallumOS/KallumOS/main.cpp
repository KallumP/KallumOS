#define OLC_PGE_APPLICATION 0
#include "KallumOS.h"
#include "olcPixelGameEngine.h"


class PixelGameEngine : public olc::PixelGameEngine {
public:
	PixelGameEngine() {
		sAppName = "KallumOS";
	}

public:
	bool OnUserCreate() override {

		frameRate = 60;
		targetFrameTime = 1 / frameRate;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {


		//keeps track of how much time has passed
		timeSinceLastFrame += fElapsedTime;

		//checks to see if enough time has passed since the last frame
		if (timeSinceLastFrame > targetFrameTime) {

			//resets the time since last frame
			timeSinceLastFrame = 0;

			//clears the window
			Clear(olc::BLACK);

			os.Tick(this, fElapsedTime);
			os.Draw(this);


		}


		return true;
	}

private:

	KallumOS os;
	float frameRate;
	float targetFrameTime;
	float timeSinceLastFrame;
};

int main() {

	PixelGameEngine window;

	if (window.Construct(1500, 750, 1, 1))
		window.Start();

	return 0;
}
