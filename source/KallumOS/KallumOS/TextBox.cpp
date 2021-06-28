
#include "TextBox.h"
#include "Point.h"

TextBox::TextBox(Point _position, Point _size) : Control(_position, _size) {

	color = olc::WHITE;
}

void TextBox::Draw(olc::PixelGameEngine* window) {

	window->FillRect(position.GetX(), position.GetY(), size.GetX(), size.GetY(), color);

	//draws red circles at the positoin and the positoin + size (to get hitboxes)
	//window->FillCircle(position.GetX(), position.GetY(), 1, olc::RED);
	//window->FillCircle(position.GetX() + size.GetX(), position.GetY() + size.GetY(), 1, olc::RED);
}

bool TextBox::Hover(Point* mousePosition) {

	if (Within(mousePosition)) {
		color = olc::RED;
	} else {
		color = olc::WHITE;
	}

	return false;
}
bool TextBox::Click(Point* mousePosition) {

	if (Within(mousePosition)) {

	}

	return false;
}

void TextBox::Append(char input) {

}
void TextBox::DeleteOne() {

}
void TextBox::DeleteWord() {

}