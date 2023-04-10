#include "TestWindow.h"

TestWindow::TestWindow(Point _position, Point _size) : Process("Test window", _position, _size) {

	std::filesystem::path appPath = "TestWindow";

	fileSelector = FileSelector(Point(200,100), Point(300,300), appPath);
}



void TestWindow::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		fileSelector.Draw();
	}
}