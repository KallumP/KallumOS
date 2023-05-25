#pragma once
#include "Process.h"
#include <string>

class TicTak : public Process {

public:
	TicTak();
	TicTak(Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);

private:
	void SetupBoard();
	void OutputConsoleBoard();
	void DrawSquare(Point offset, int i, int j, Color c);

	void CheckWin();
	
	Point square;
	int board[3][3];
	int turn;
	bool win;

	std::string message;
	Color messageColor;
};

