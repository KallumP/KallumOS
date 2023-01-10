#include "Tetris.h"
#include <array>


Tetris::Tetris(Point _position, Point _size) : Process("Tetris", _position, _size) {

	ResetBoard();

	Piece* foo = new Piece();
	foo->color = BLUE;
	SetPiece(Point(3, 2), foo);

	Piece* bar = new Piece();
	bar->color = RED;
	SetPiece(Point(4, 7), bar);
	SpawnPiece();

}


void Tetris::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		offset.SetX(offset.GetX() + 5);
		offset.SetY(offset.GetY() + 5);

		//DrawText(position.ToString().c_str(), 10 + offset.GetX(), 5 + offset.GetY(), defaultFontSize, BLACK);

		DrawBoardBoarders(offset);

		DrawPieces(offset);

	}

}

void Tetris::DrawBoardBoarders(Point offset) {

	//draws all vertical lines
	for (int i = 0; i < boardWidth + 1; i++)
		DrawLine(offset.GetX() + pieceSize * i, offset.GetY(), offset.GetX() + pieceSize * i, offset.GetY() + boardHeight * pieceSize, BLACK);

	//draws all horizontal lines
	for (int i = 0; i < boardHeight + 1; i++)
		DrawLine(offset.GetX(), offset.GetY() + pieceSize * i, offset.GetX() + boardWidth * pieceSize, offset.GetY() + pieceSize * i, BLACK);
}


void Tetris::DrawPieces(Point offset) {

	//loops through the board
	for (int i = 0; i < boardWidth; i++)
		for (int j = 0; j < boardHeight; j++)

			//if there was a piece here
			if (board[i][j] != nullptr)

				//draw the piece
				DrawRectangle(offset.GetX() + pieceSize * i, offset.GetY() + pieceSize * j, pieceSize, pieceSize, board[i][j]->color);
}




void Tetris::OnKeyPress(KeyPress* e) {

}
void Tetris::OnMousePress(MousePress* e, int taskbarHeight) {
}

void Tetris::Tick() {


}

void Tetris::ResetBoard() {

	for (int i = 0; i < boardWidth; i++)

		for (int j = 0; j < boardHeight; j++)

			board[i][j] = nullptr;
}

void Tetris::SetPiece(Point loc, Piece* piece) {

	board[loc.GetX()][loc.GetY()] = piece;

}

void Tetris::SpawnPiece() {

	Point spawnLocation = Point(0, 5);


}

