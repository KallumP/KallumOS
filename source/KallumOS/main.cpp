#define OLC_PGE_APPLICATION 0
#include "raylib.h"

#include "KallumOS.h"
#include "Input.h"
#include "Helper.h"

int main() {

	//sets up the window
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 750, "KallumOS");

	Helper::SetupHelper();
	
	if (!Helper::CreateHardDrive())
		return 0;

	KallumOS* os = new KallumOS();
	Input* inputHandler = new Input();

	float targetFrameRate = 60;
	float targetFrameTime = 1 / targetFrameRate;
	float timeSinceLastFrame = 0;
	float runtime = 0;

	while (!WindowShouldClose()) {

		timeSinceLastFrame = GetFrameTime();
		runtime += timeSinceLastFrame;

		inputHandler->GetKeyPress(timeSinceLastFrame, os);
		inputHandler->GetMouseInputs(timeSinceLastFrame, os);
		inputHandler->GetMouseMovement(timeSinceLastFrame, os);

		os->Tick(timeSinceLastFrame);
		timeSinceLastFrame = 0;

		BeginDrawing();
		os->Draw();
		EndDrawing();
	}

	return 0;
}
