#include "Tetris.h"
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>

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
				DrawRectangle(
					offset.GetX() + pieceSize * i,
					offset.GetY() + pieceSize * j,
					pieceSize, pieceSize, board[i][j]->color);

	//draws the falling piece
	for (int i = 0; i < 4; i++)
		DrawRectangle(
			offset.GetX() + pieceSize * fallingPiece[i]->location.GetX(),
			offset.GetY() + pieceSize * fallingPiece[i]->location.GetY(),
			pieceSize, pieceSize, fallingPiece[i]->color);
}


void Tetris::OnKeyPress(KeyPress* e) {

	if (display) {

		if (e->GetKeyCode() == KEY_J)
			SlideSpawned(true);
		else if (e->GetKeyCode() == KEY_L)
			SlideSpawned(false);
		else if (e->GetKeyCode() == KEY_K)
			DropSpawned();
		else if (e->GetKeyCode() == KEY_SPACE)
			HardDropSpawned();
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

	//random number between 1 and 7
	std::srand(std::time(nullptr));
	int randomNumber = std::rand() % 7 + 1;

	//chooses a spawn type from the random number
	if (randomNumber == 1)
		SpawnTBlock(spawnLocation);
	else if (randomNumber == 2)
		SpawnLineBlock(spawnLocation);
	else if (randomNumber == 3)
		SpawnLBlock(spawnLocation);
	else if (randomNumber == 4)
		SpawnReverseLBlock(spawnLocation);
	else if (randomNumber == 5)
		SpawnOBlock(spawnLocation);
	else if (randomNumber == 6)
		SpawnSBlock(spawnLocation);
	else if (randomNumber == 7)
		SpawnReverseSBlock(spawnLocation);
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

//drops the falling piece down one
void Tetris::DropSpawned() {

	//makes a copy of the falling piece
	std::array<FallingBlock*, 4> tempFalling = FreshFalling();
	CopyFalling(tempFalling, fallingPiece);

	//moves the copy
	ShiftSpawned(tempFalling, 0, 0, 1, 0);


	//checks if the copy doesn't collide with anything
	if (!CheckCollisionY(tempFalling)) {

		//copies the copied falling piece values into the falling piece
		CopyFalling(fallingPiece, tempFalling);

		//if there was a collision
	} else {

		//dont copy the moved temporary piece and set the board
		SetFallingPiece();
		SpawnPiece();
	}
}

//moves the falling block on the x-axis
void Tetris::SlideSpawned(bool left) {

	int rightMove = 0;
	int leftMove = 0;
	if (left)
		leftMove++;
	else
		rightMove++;

	//makes a copy of the falling piece
	std::array<FallingBlock*, 4> tempFalling = FreshFalling();
	CopyFalling(tempFalling, fallingPiece);

	//moves the copy
	ShiftSpawned(tempFalling, leftMove, rightMove, 0, 0);

	//checks if the copy doesn't collide with anything
	if (!CheckCollisionX(tempFalling))

		//copies the copied falling piece values into the falling piece
		CopyFalling(fallingPiece, tempFalling);
}

void Tetris::HardDropSpawned() {

	//makes a copy of the falling piece
	std::array<FallingBlock*, 4> tempFalling = FreshFalling();
	CopyFalling(tempFalling, fallingPiece);


	std::array<FallingBlock*, 4> previous = FreshFalling();
	CopyFalling(previous, fallingPiece);

	do {

		//makes a copy of the current temporaryFalling block
		CopyFalling(previous, tempFalling);

		//moves the copy
		ShiftSpawned(tempFalling, 0, 0, 1, 0);

		//while there was no collision
	} while (!CheckCollisionY(tempFalling));

	//copies the copied falling piece values into the falling piece
	CopyFalling(fallingPiece, previous);

	SetFallingPiece();
	SpawnPiece();
}

//moves the falling block by the units passed
void Tetris::ShiftSpawned(std::array<FallingBlock*, 4> toMove, int left, int right, int down, int up) {

	for (int i = 0; i < 4; i++) {
		toMove[i]->location.SetX(toMove[i]->location.GetX() + right - left);
		toMove[i]->location.SetY(toMove[i]->location.GetY() + down - up);
	}
}

//returns if the falling piece has collided
bool Tetris::CheckCollisionX(std::array<FallingBlock*, 4> toCheck) {

	//x-axis collisions
	for (int i = 0; i < 4; i++) {

		//checks if this is out of the board
		if (toCheck[i]->location.GetX() < 0 || toCheck[i]->location.GetX() > boardWidth - 1)
			return true;

		//checks if this location was occupied
		if (board[toCheck[i]->location.GetX()][toCheck[i]->location.GetY()] != nullptr)
			return true;
	}

	return false;
}

bool Tetris::CheckCollisionY(std::array<FallingBlock*, 4> toCheck) {

	//y-axis collision
	for (int i = 0; i < 4; i++) {

		//checks if this is out of the board
		if (toCheck[i]->location.GetY() > boardHeight - 1)
			return true;

		//checks if this location was occupied
		if (board[toCheck[i]->location.GetX()][toCheck[i]->location.GetY()] != nullptr) 
			return true;
	}

	return false;
}

//turns each falling block in the falling piece into a permanent piece
void Tetris::SetFallingPiece() {

	for (int i = 0; i < 4; i++)
		SetPiece(Point(fallingPiece[i]->location.GetX(), fallingPiece[i]->location.GetY()), new Block(fallingPiece[i]->color));
}

//creates a fresh array of falling piece blocks
std::array<FallingBlock*, 4> Tetris::FreshFalling() {

	std::array<FallingBlock*, 4> tempFalling;

	for (int i = 0; i < 4; i++)
		tempFalling[i] = new FallingBlock(Point(0, 0), RED);

	return tempFalling;
}

//returns a copy of the falling piece
void Tetris::CopyFalling(std::array<FallingBlock*, 4> copyTo, std::array<FallingBlock*, 4> copyFrom) {

	for (int i = 0; i < 4; i++) {

		copyTo[i]->location.SetX(copyFrom[i]->location.GetX());
		copyTo[i]->location.SetY(copyFrom[i]->location.GetY());
	}
}