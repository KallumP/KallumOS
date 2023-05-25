#include "TestWindow.h"

TestWindow::TestWindow(Point _position, Point _size) : Process("Test window", _position, _size) {

	std::filesystem::path appPath = "TestWindow";

	foo = "Nothing selected yet";
	fileSelector = new FileSelector(Point(200, 100), Point(300, 300), appPath);
}



void TestWindow::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		DrawText(foo.c_str(), offset.GetX() + 10, offset.GetY() + 20, 20, BLACK);

		if (fileSelector != nullptr)
			fileSelector->Draw(Point(0, 0));
	}
}

void TestWindow::Tick(float elapsedTime) {

	if (fileSelector != nullptr) {

		fileSelector->Hover(new Point(GetMouseX(), GetMouseY()));

		if (fileSelector->GetReady()) {
			foo = fileSelector->GetSelectedFile();
			delete fileSelector;
			fileSelector = nullptr;
		}
	}

}

void TestWindow::OnMousePress(MousePress* e, int taskbarHeight) {

	if (display) {

		SuperMousePress(NormaliseMousePos(taskbarHeight));

		if (fileSelector != nullptr)
			fileSelector->Click(new Point(GetMouseX(), GetMouseY()));
	}
}

