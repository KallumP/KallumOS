#pragma once
#include "Process.h"
#include <array>


struct Piece {
	Color color;
};

class Tetris : public Process {

public:
	Tetris();
	Tetris(Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);

	void Tick();

private:

	void DrawBoardBoarders(Point offset);
	void DrawPieces(Point offset);

	void ResetBoard();
	void SpawnPiece();

	void SetPiece(Point loc, Piece* piece);


	static const int boardWidth = 10;
	static const int boardHeight = 20;
	static const int pieceSize = 30;

	std::array<std::array<Piece*, boardHeight>, boardWidth> board;

	std::array<std::array<Piece*, 4>, 4> falling;

	
};



