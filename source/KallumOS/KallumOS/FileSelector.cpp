#include "FileSelector.h"


FileSelector::FileSelector() : Control() {}

FileSelector::FileSelector(Point _position, Point _size) : Control(_position, _size) {}


void FileSelector::Draw() {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(GetScreenWidth(), GetScreenHeight()));

	//draws the button
	DrawRectangle(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), backColor);

	//draws the textbox value
	DrawText("File selector", normalizedPosition->GetX() + padding.GetX(), normalizedPosition->GetY() + padding.GetY(), fontSize, fontColor);

	//draws the focus outline
	if (focused)
		DrawRectangleLines(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), BLACK);
}

bool FileSelector::Click(Point* mousePosition) {

	return false;
}
