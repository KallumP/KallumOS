#include "AppLauncher.h"


AppLauncher::AppLauncher(std::vector<Process*>* _processes, Point _position, Point _size) : Process("App launcher", _position, _size) {

	processes = _processes;

	SetupProcessInfos();

	scrollUp = Button(Point(30, 30), Point(100, 30), "Scroll Up");
	scrollUp.Tether(&position);
	scrollUp.SetFontSize(10);
}

void AppLauncher::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		scrollUp.Draw();

		int padding = 30;
		for (int i = 0; i < processInfos.size(); i++) {

			DrawRectangleLines(
				offset.GetX() + ProcessInfo::buttonPadding,
				offset.GetY() + ProcessInfo::buttonPadding * (i + 1) + processInfos[i].buttonSizes.GetY() * i,
				processInfos[i].buttonSizes.GetX(),
				processInfos[i].buttonSizes.GetY(),
				RED);

			DrawText(
				processInfos[i].processName.c_str(),
				offset.GetX() + ProcessInfo::buttonPadding * 1.5,
				offset.GetY() + ProcessInfo::buttonPadding * (i + 1) + processInfos[i].buttonSizes.GetY() * i + processInfos[i].buttonSizes.GetY() * 0.5,
				defaultFontSize,
				BLACK);

		}
	}
}

void AppLauncher::OnKeyPress(KeyPress* e) {

	if (display) {

	}
}

void AppLauncher::OnMousePress(MousePress* e) {

	if (display) {

		SuperMousePress(NormaliseMousePos());

		Point normalisedMouse = NormaliseMousePos(barHeight);

		//loops through all the possible apps
		for (int i = 0; i < processInfos.size(); i++) {

			//checks if the mouse was within the x of the buttons
			if (normalisedMouse.GetX() > ProcessInfo::buttonPadding && 
				normalisedMouse.GetX() < ProcessInfo::buttonPadding + processInfos[i].buttonSizes.GetX()) {

				//checks if the mouse was within the y of the buttons
				if (normalisedMouse.GetY() > ProcessInfo::buttonPadding * (i + 1) + processInfos[i].buttonSizes.GetY() * i &&
					normalisedMouse.GetY() < ProcessInfo::buttonPadding * (i + 1) + processInfos[i].buttonSizes.GetY() * i + processInfos[i].buttonSizes.GetY()) {

					//calls the right method to open the clicked app
					if (processInfos[i].processName == "Task Manager") {

						TaskManager* app = new TaskManager(processes, Point(200, 60), Point(450, 300));
						app->BindCloseApp(CloseApp);
						LaunchApp(app);

					} else if (processInfos[i].processName == "Text Editor") {

						TextEditor* app = new TextEditor(Point(700, 60), Point(400, 200));
						LaunchApp(app);

					} else if (processInfos[i].processName == "Tic Tak") {

						TicTak* app = new TicTak(Point(700, 350), Point(400, 200));
						LaunchApp(app);

					} else if (processInfos[i].processName == "Tetris") {
						Tetris* app = new Tetris(Point(525, 60));
						LaunchApp(app);

					} else if (processInfos[i].processName == "Kode") {
						Kode* app = new Kode(Point(525, 60), Point(700, 500));
						LaunchApp(app);

					} else if (processInfos[i].processName == "Test") {
						TestWindow* app = new TestWindow(Point(525, 60), Point(700, 500));
						LaunchApp(app);
					}
				}
			}
		}
	}
}

void AppLauncher::SetupProcessInfos() {

	ProcessInfo test = ProcessInfo("Test");
	processInfos.push_back(test);

	ProcessInfo manager = ProcessInfo("Task Manager");
	processInfos.push_back(manager);

	ProcessInfo kode = ProcessInfo("Kode");
	processInfos.push_back(kode);

	ProcessInfo word = ProcessInfo("Text Editor");
	processInfos.push_back(word);

	ProcessInfo tic = ProcessInfo("Tic Tak");
	processInfos.push_back(tic);

	ProcessInfo tetris = ProcessInfo("Tetris");
	processInfos.push_back(tetris);

}
