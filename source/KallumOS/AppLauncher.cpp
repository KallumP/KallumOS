#include "kGraphics.h"
#include "AppLauncher.h"
#include "Helper.h"


AppLauncher::AppLauncher(std::vector<Process*>* _processes, Point _position, Point _size) : Process("App launcher", _position, _size) {

	processes = _processes;

	SetupProcessInfos();

	displayStart = 0;
	scrollUp = Button(Point(30, 40), Point(40, 30), "/\\");
	scrollUp.Tether(&position);
	scrollUp.SetFontSize(10);

	scrollDown = Button(Point(90, 40), Point(40, 30), "\\/");
	scrollDown.Tether(&position);
	scrollDown.SetFontSize(10);
}

void AppLauncher::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		scrollUp.Draw();
		scrollDown.Draw();

		int scrollButtonPadding = scrollUp.GetSize().GetY();


		int height = size.GetY();
		height -= scrollUp.GetSize().GetY() + scrollButtonPadding;

		int buttonCount = height / (ProcessInfo::buttonPadding + ProcessInfo::buttonSizes.GetY());

		for (int i = displayStart; i < processInfos.size(); i++) {

			int zeroBasedI = i - displayStart;

			if (zeroBasedI > buttonCount - 1)
				break;
			
			kGraphics::DrawRect(
				offset.GetX() + ProcessInfo::buttonPadding,
				offset.GetY() + scrollUp.GetSize().GetY() + scrollButtonPadding + (ProcessInfo::buttonPadding + ProcessInfo::buttonSizes.GetY()) * zeroBasedI,
				ProcessInfo::buttonSizes.GetX(),
				ProcessInfo::buttonSizes.GetY(),
				RED);


			std::string toDisplay = std::to_string(i) + ": " + processInfos[i].processName;
			kGraphics::DrawString(
				toDisplay,
				offset.GetX() + ProcessInfo::buttonPadding * 1.5,
				offset.GetY() + scrollUp.GetSize().GetY() + scrollButtonPadding + (ProcessInfo::buttonPadding + ProcessInfo::buttonSizes.GetY()) * zeroBasedI + ProcessInfo::buttonSizes.GetY() * 0.5,
				defaultFontSize,
				BLACK);

		}
	}
}

void AppLauncher::Tick(float elapsedTime) {

	scrollUp.Hover(new Point(GetMouseX(), GetMouseY()));
	scrollDown.Hover(new Point(GetMouseX(), GetMouseY()));

}

void AppLauncher::OnKeyPress(KeyPress* e) {

	if (display) {

	}
}

void AppLauncher::OnMousePress(MousePress* e) {

	if (display) {

		SuperMousePress(Helper::NormaliseMousePos(position));

		HandleButtonClicks();

		Point normalisedMouse = Helper::NormaliseMousePos(position, barHeight);

		int scrollButtonPadding = scrollUp.GetSize().GetY();

		//loops through all the possible apps
		for (int i = displayStart; i < processInfos.size(); i++) {

			int zeroBasedI = i - displayStart;

			//checks if the mouse was within the x of the buttons
			if (normalisedMouse.GetX() > ProcessInfo::buttonPadding &&
				normalisedMouse.GetX() < ProcessInfo::buttonPadding + processInfos[i].buttonSizes.GetX()) {

				//checks if the mouse was within the y of the buttons
				if (normalisedMouse.GetY() - scrollButtonPadding > ProcessInfo::buttonPadding * (zeroBasedI + 1) + processInfos[i].buttonSizes.GetY() * zeroBasedI &&
					normalisedMouse.GetY() - scrollButtonPadding < ProcessInfo::buttonPadding * (zeroBasedI + 1) + processInfos[i].buttonSizes.GetY() * zeroBasedI + processInfos[i].buttonSizes.GetY()) {

					//calls the right method within the clicked button to open the app
					processInfos[i].launchCode();
				}
			}
		}
	}
}

void AppLauncher::HandleButtonClicks() {

	if (scrollUp.Click(new Point(GetMouseX(), GetMouseY())))
		displayStart--;

	else if (scrollDown.Click(new Point(GetMouseX(), GetMouseY())))
		displayStart++;

	displayStart = Helper::Constrain(displayStart, 0, processInfos.size() - 1);
}

void AppLauncher::SetupProcessInfos() {

	std::function<void()> launchCode;

	/*launchCode = [this]() {
		TestWindow* app = new TestWindow(Point(525, 60), Point(700, 500));
		LaunchApp(app);
	};
	ProcessInfo test = ProcessInfo("Test", launchCode);
	processInfos.push_back(test);*/


	launchCode = [this]() {
		DiffMatrixApp* app = new DiffMatrixApp(Point(525, 60), Point(700, 500));
		LaunchApp(app);
	};
	ProcessInfo diff = ProcessInfo("Diff", launchCode);
	processInfos.push_back(diff);


	launchCode = [this]() {
		Kode* app = new Kode(Point(525, 60), Point(700, 500));
		LaunchApp(app);
	};
	ProcessInfo kode = ProcessInfo("Kode", launchCode);
	processInfos.push_back(kode);


	launchCode = [this]() {
		TaskManager* app = new TaskManager(processes, Point(200, 60), Point(450, 300));
		app->BindCloseApp(CloseApp);
		LaunchApp(app);
	};
	ProcessInfo manager = ProcessInfo("Task Manager", launchCode);
	processInfos.push_back(manager);


	launchCode = [this]() {
		Tetris* app = new Tetris(Point(525, 60));
		LaunchApp(app);
	};
	ProcessInfo tetris = ProcessInfo("Tetris", launchCode);
	processInfos.push_back(tetris);


	launchCode = [this]() {
		TextEditor* app = new TextEditor(Point(700, 60), Point(400, 200));
		LaunchApp(app);
	};
	ProcessInfo word = ProcessInfo("Text Editor", launchCode);
	processInfos.push_back(word);


	launchCode = [this]() {
		TicTak* app = new TicTak(Point(700, 350), Point(400, 200));
		LaunchApp(app);
	};
	ProcessInfo tic = ProcessInfo("Tic Tak", launchCode);
	processInfos.push_back(tic);
}
