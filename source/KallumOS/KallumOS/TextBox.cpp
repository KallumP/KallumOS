
#include "TextBox.h"
#include "Point.h"


TextBox::TextBox(olc::PixelGameEngine* _window, Point _position, Point _size) : Control(_window, _position, _size) {

	color = olc::WHITE;
}

void TextBox::Draw() {

	Point* normalizedPosition = new Point();
	*normalizedPosition = normalizePosition(new Point(window->ScreenWidth(), window->ScreenHeight()));

	window->FillRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), color);

	if (focused)
		window->DrawRect(normalizedPosition->GetX(), normalizedPosition->GetY(), size.GetX(), size.GetY(), olc::BLACK);

	//draws red circles at the positoin and the positoin + size (to get hitboxes)
	//window->FillCircle(position.GetX(), position.GetY(), 1, olc::RED);
	//window->FillCircle(position.GetX() + size.GetX(), position.GetY() + size.GetY(), 1, olc::RED);
}

bool TextBox::Hover(Point* mousePosition) {

	if (Within(mousePosition)) {

		color = olc::RED;
		return true;
	}

	color = olc::WHITE;
	return false;
}
bool TextBox::Click(Point* mousePosition) {

	if (Within(mousePosition))
		return true;

	return false;
}

void TextBox::Append(char input) {

}
void TextBox::DeleteOne() {

}
void TextBox::DeleteWord() {

}