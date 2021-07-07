#define OLC_PGE_APPLICATION 0
#include "olcPixelGameEngine.h"
#include "KallumOS.h"

class PixelGameEngine : public olc::PixelGameEngine {
public:
	PixelGameEngine() {
		sAppName = "KallumOS";
	}

public:
	bool OnUserCreate() override {

		os = new KallumOS(this);

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

			os->Tick(fElapsedTime);
			os->Draw();

		}

		return true;
	}

private:

	KallumOS* os;
	float frameRate;
	float targetFrameTime;
	float timeSinceLastFrame;
};

int main() {

	PixelGameEngine* window = new PixelGameEngine();

	if (window->Construct(1000, 700, 1, 1))
		window->Start();

	return 0;
}
