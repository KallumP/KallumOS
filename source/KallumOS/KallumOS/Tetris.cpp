#include "Tetris.h"
#include <array>
#include <string>
#include <iostream>


Tetris::Tetris(Point _position, Point _size) : Process("Tetris", _position, _size) {

	timeSinceLastFrame = 0;
	targetFrameRate = 10;

	framesPerDrop = 5;
	framesTillNextDrop = 0;

	ResetBoard();
	SpawnPiece();
}


void Tetris::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		offset.SetX(offset.GetX() + 5);
		offset.SetY(offset.GetY() + 5);

		DrawText(std::to_string(timeSinceLastFrame).c_str(), 10 + offset.GetX(), 5 + offset.GetY(), defaultFontSize, BLACK);

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

	//loops through the board and draws the piece if there was one
	for (int i = 0; i < boardWidth; i++)
		for (int j = 0; j < boardHeight; j++)
			if (board[i][j] != nullptr)
				DrawRectangle(offset.GetX() + pieceSize * i, offset.GetY() + pieceSize * j, pieceSize, pieceSize, board[i][j]->color);

	//draws the falling piece
	for (int i = 0; i < 4; i++)
		DrawRectangle(offset.GetX() + pieceSize * fallingPiece[i]->location.GetX(), offset.GetY() + pieceSize * fallingPiece[i]->location.GetY(), pieceSize, pieceSize, fallingPiece[i]->color);
}


void Tetris::OnKeyPress(KeyPress* e) {

	if (display) {

		if (e->GetKeyCode() == KEY_J)
			ShiftSpawned(true);
		else if (e->GetKeyCode() == KEY_L)
			ShiftSpawned(false);

	}

}
void Tetris::OnMousePress(MousePress* e, int taskbarHeight) {
}

void Tetris::Tick(float elapsedTime) {

	//gets the time in between ticks
	timeSinceLastFrame += elapsedTime;

	//checks if enough time has been for another frame
	if (timeSinceLastFrame > 1 / (double)targetFrameRate) {

		//resets the time for the next frame
		timeSinceLastFrame = 0;
		
		//gets how many frames has occured since the last 
		framesTillNextDrop++;
		if (framesTillNextDrop >= framesPerDrop) {
			
			framesTillNextDrop = 0;

			DropSpawned();
		}
	}
}

void Tetris::ResetBoard() {

	for (int i = 0; i < boardWidth; i++)

		for (int j = 0; j < boardHeight; j++)

			board[i][j] = nullptr;
}

void Tetris::SetPiece(Point loc, Block* piece) {

	board[loc.GetX()][loc.GetY()] = piece;

}

void Tetris::SpawnPiece() {

	Point spawnLocation = Point(4, 0);


	SpawnSBlock(spawnLocation);

}

void Tetris::SpawnTBlock(Point spawnLocation) {
	fallingPiece[0] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0), MAGENTA);
	fallingPiece[1] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0), MAGENTA);
	fallingPiece[2] = new FallingBlock(Point(spawnLocation.GetX() + 2, spawnLocation.GetY() + 0), MAGENTA);
	fallingPiece[3] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1), MAGENTA);
}
void Tetris::SpawnLineBlock(Point spawnLocation) {
	fallingPiece[0] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0), SKYBLUE);
	fallingPiece[1] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1), SKYBLUE);
	fallingPiece[2] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 2), SKYBLUE);
	fallingPiece[3] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 3), SKYBLUE);
}
void Tetris::SpawnLBlock(Point spawnLocation) {
	fallingPiece[0] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0), ORANGE);
	fallingPiece[1] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1), ORANGE);
	fallingPiece[2] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 2), ORANGE);
	fallingPiece[3] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 2), ORANGE);
}
void Tetris::SpawnReverseLBlock(Point spawnLocation) {
	fallingPiece[0] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0), DARKBLUE);
	fallingPiece[1] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1), DARKBLUE);
	fallingPiece[2] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 2), DARKBLUE);
	fallingPiece[3] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 2), DARKBLUE);
}
void Tetris::SpawnOBlock(Point spawnLocation) {
	fallingPiece[0] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0), YELLOW);
	fallingPiece[1] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1), YELLOW);
	fallingPiece[2] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0), YELLOW);
	fallingPiece[3] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1), YELLOW);
}
void Tetris::SpawnSBlock(Point spawnLocation) {

	fallingPiece[0] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0), LIME);
	fallingPiece[1] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1), LIME);
	fallingPiece[2] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0), LIME);
	fallingPiece[3] = new FallingBlock(Point(spawnLocation.GetX() + 2, spawnLocation.GetY() + 1), LIME);
}
void Tetris::SpawnReverseSBlock(Point spawnLocation) {
	fallingPiece[0] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0), RED);
	fallingPiece[1] = new FallingBlock(Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1), RED);
	fallingPiece[2] = new FallingBlock(Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1), RED);
	fallingPiece[3] = new FallingBlock(Point(spawnLocation.GetX() + 2, spawnLocation.GetY() + 0), RED);
}

void Tetris::DropSpawned() {

	//draws the falling piece
	for (int i = 0; i < 4; i++) {

		fallingPiece[i]->location.SetY(fallingPiece[i]->location.GetY() + 1);
	}

}

void Tetris::ShiftSpawned(bool left) {


	int toMove = 1;
	if (left)
		toMove *= -1;

	//draws the falling piece
	for (int i = 0; i < 4; i++) {

		fallingPiece[i]->location.SetX(fallingPiece[i]->location.GetX() + toMove);
	}
}