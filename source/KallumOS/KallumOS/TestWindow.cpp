#include "TestWindow.h"

TestWindow::TestWindow(Point _position, Point _size) : Process("Test window", _position, _size) {

}



void TestWindow::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

	}
}