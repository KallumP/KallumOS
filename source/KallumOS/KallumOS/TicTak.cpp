#include "TicTak.h"

TicTak::TicTak(Point _position, Point _size) : Process("Tic Tak", _position, _size) {

	turn = 1;
	win = false;

	message = "Player" + std::to_string(turn) + "'s turn";
	messageColor = BLACK;

	SetupBoard();
	OutputConsoleBoard();
}

void TicTak::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)

				if (board[i][j] == 1)
					DrawSquare(offset, i, j, BLUE);
				else if (board[i][j] == 2)
					DrawSquare(offset, i, j, YELLOW);
		}

		DrawText(message.c_str(), 10 + offset.GetX(), 5 + offset.GetY() + square.GetY() * 3, defaultFontSize, messageColor);
	}
}

void TicTak::OnKeyPress(KeyPress* e) {

	if (display) {

		if (e->GetKeyCode() == KEY_R)
			SetupBoard();
	}
}

void TicTak::OnMousePress(MousePress* e, int taskbarHeight) {

	if (display) {

		SuperMousePress(NormaliseMousePos(taskbarHeight));

		Point normalisedMouse = NormaliseMousePos(taskbarHeight + barHeight);


		if (!win) {

			int clickX = (int)std::floor(normalisedMouse.GetX() / square.GetX());
			int clickY = (int)std::floor(normalisedMouse.GetY() / square.GetY());

			if (clickX >= 0 && clickX <= 2 && clickY >= 0 && clickY <= 2) {

				if (board[clickX][clickY] == 0) {

					board[clickX][clickY] = turn;

					OutputConsoleBoard();

					turn = 2 / turn;

					message = "Player" + std::to_string(turn) + "'s turn";
					messageColor = BLACK;

					CheckWin();

				} else {

					message = "Cannot select this square";
					messageColor = RED;
				}

			} else {

				//message = "Click within the window";
				//messageColor = RED;
			}
		}
	}
}







void TicTak::SetupBoard() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = 0;

	square = Point(size.GetX() / 3, (size.GetY() - 20) / 3);

	turn = 1;
	win = false;

	message = "Player" + std::to_string(turn) + "'s turn";
	messageColor = BLACK;
}

void TicTak::OutputConsoleBoard() {

}

void TicTak::DrawSquare(Point offset, int i, int j, Color c) {

	DrawRectangle(offset.GetX() + square.GetX() * i, offset.GetY() + square.GetY() * j, square.GetX(), square.GetY(), c);

}

void TicTak::CheckWin() {


	//horizontals
	win = false;
	win = win || board[0][0] != 0 && board[0][0] == board[1][0] && board[0][0] == board[2][0];
	win = win || board[0][1] != 0 && board[0][1] == board[1][1] && board[0][1] == board[2][1];
	win = win || board[0][2] != 0 && board[0][2] == board[1][2] && board[0][2] == board[2][2];


	//verticals
	win = win || board[0][0] != 0 && board[0][0] == board[0][1] && board[0][0] == board[0][2];
	win = win || board[1][0] != 0 && board[1][0] == board[1][1] && board[1][0] == board[1][2];
	win = win || board[2][0] != 0 && board[2][0] == board[2][1] && board[2][0] == board[2][2];


	//diagonals
	win = win || board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2];
	win = win || board[2][0] != 0 && board[2][0] == board[1][1] && board[2][0] == board[0][2];



	if (win) {

		message = "Player " + std::to_string(2 / turn) + " won";
		messageColor = GREEN;
	}
}
