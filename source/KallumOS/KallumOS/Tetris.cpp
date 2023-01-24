#include "Tetris.h"
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>

Tetris::Tetris(Point _position, Point _size) : Process("Tetris", _position, _size) {

	timeSinceLastFrame = 0;
	targetFrameRate = 10;

	dropDelay = 5;
	framesSinceLastDrop = 0;

	setDelay = 3;
	framesSinceLastSet = 0;

	ResetBoard();
	SpawnPiece();
}


void Tetris::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		offset.SetX(offset.GetX() + 5);
		offset.SetY(offset.GetY() + 5);

		DrawPieces(offset);
		DrawBoardBoarders(offset);

		//DrawText(std::to_string(framesSinceLastSet).c_str(), offset.GetX() + 10, offset.GetY(), defaultFontSize, BLACK);
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

	//draws the shadow
	UpdateShadow();
	for (int i = 0; i < 4; i++)
		DrawRectangle(
			offset.GetX() + pieceSize * fallingPieceShadow[i]->location.GetX(),
			offset.GetY() + pieceSize * fallingPieceShadow[i]->location.GetY(),
			pieceSize, pieceSize, fallingPieceShadow[i]->color);

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
			DropSpawned(true);
		else if (e->GetKeyCode() == KEY_SPACE)
			HardDropSpawned();
		else if (e->GetKeyCode() == KEY_I)
			RotateSpawned();
		else if (e->GetKeyCode() == KEY_W)
			for (int i = 0; i < 3; i++)
				RotateSpawned();
		else if (e->GetKeyCode() == KEY_D)
			for (int i = 0; i < 2; i++)
				RotateSpawned();
	}
}
void Tetris::OnMousePress(MousePress* e, int taskbarHeight) {

	if (display) {

		CheckBarButtonsClicked(NormaliseMousePos(taskbarHeight));

		Point normalisedMouse = NormaliseMousePos(taskbarHeight + barHeight);
	}
}

void Tetris::Tick(float elapsedTime) {

	//gets the time in between ticks
	timeSinceLastFrame += elapsedTime;

	//checks if enough time has been for another frame
	if (timeSinceLastFrame > 1 / (double)targetFrameRate) {

		//resets the time for the next frame
		timeSinceLastFrame = 0;

		//gets how many frames has occured since the last 
		framesSinceLastDrop++;
		if (framesSinceLastDrop >= dropDelay) {

			framesSinceLastDrop = 0;

			DropSpawned(false);
		}
	}
}

void Tetris::ResetBoard() {

	for (int i = 0; i < boardWidth; i++)

		for (int j = 0; j < boardHeight; j++)

			board[i][j] = nullptr;

	fallingPieceShadow = FreshFalling();
}

void Tetris::SetBlock(Point loc, Block* piece) {

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
void Tetris::DropSpawned(bool softDrop) {

	//makes a copy of the falling piece
	std::array<FallingBlock*, 4> tempFalling = FreshFalling();
	CopyFalling(tempFalling, fallingPiece);

	//moves the copy
	ShiftSpawned(tempFalling, 0, 0, 1, 0);

	//checks if the copy doesn't collide with anything
	if (!CheckBoardCollisionY(tempFalling) && !CheckPieceCollision(tempFalling)) {

		//copies the copied falling piece values into the falling piece
		CopyFalling(fallingPiece, tempFalling);

		framesSinceLastSet = 0;

		//if there was a collision
	} else {

		//if this wasn't a soft drop (only tries to set on the tick not keypress)
		if (!softDrop) {

			//dont copy the moved temporary piece and set the board
			SetFallingPiece(true);
		}
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
	if (!CheckBoardCollisionX(tempFalling) && !CheckPieceCollision(tempFalling))

		//copies the copied falling piece values into the falling piece
		CopyFalling(fallingPiece, tempFalling);
}

//drops a piece as far as it goes
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
	} while (!CheckBoardCollisionY(tempFalling) && !CheckPieceCollision(tempFalling));

	//copies the copied falling piece values into the falling piece
	CopyFalling(fallingPiece, previous);

	SetFallingPiece(false);
}

//rotates the piece
void Tetris::RotateSpawned() {

	//makes a copy of the falling piece
	std::array<FallingBlock*, 4> rotatedFalling = FreshFalling();
	CopyFalling(rotatedFalling, fallingPiece);

	//gets the point to rotate around
	int rotateAroundIndex = 1;
	int a = fallingPiece[1]->location.GetX();
	int b = fallingPiece[1]->location.GetY();

	//rotates each block around the rotation point
	for (int i = 0; i < 4; i++) {

		int x = fallingPiece[i]->location.GetX();
		int y = fallingPiece[i]->location.GetY();

		rotatedFalling[i]->location.SetX(a + b - y);
		rotatedFalling[i]->location.SetY(x + b - a);
	}

	//checks if the copy doesn't collide with anything
	if (!CheckBoardCollisionY(rotatedFalling) && !CheckBoardCollisionX(rotatedFalling) && !CheckPieceCollision(rotatedFalling)) {

		//Copies the temporary piece into the falling Piece
		CopyFalling(fallingPiece, rotatedFalling);
	}
}

//moves the falling block by the units passed
void Tetris::ShiftSpawned(std::array<FallingBlock*, 4> toMove, int left, int right, int down, int up) {

	for (int i = 0; i < 4; i++) {
		toMove[i]->location.SetX(toMove[i]->location.GetX() + right - left);
		toMove[i]->location.SetY(toMove[i]->location.GetY() + down - up);
	}
}

//returns if the falling piece has collided on the x-axis of the board
bool Tetris::CheckBoardCollisionX(std::array<FallingBlock*, 4> toCheck) {

	//checks if any block is out of the board
	for (int i = 0; i < 4; i++)
		if (toCheck[i]->location.GetX() < 0 || toCheck[i]->location.GetX() > boardWidth - 1)
			return true;
	return false;
}

//returns if the falling piece has collided on the y-axis of the board
bool Tetris::CheckBoardCollisionY(std::array<FallingBlock*, 4> toCheck) {

	//checks if any block is out of the board
	for (int i = 0; i < 4; i++)
		if (toCheck[i]->location.GetY() > boardHeight - 1)
			return true;
	return false;
}

//returns if the falling piece has collided with any board piece
bool Tetris::CheckPieceCollision(std::array<FallingBlock*, 4> toCheck) {

	//checks if any block is intersecting with any other piece
	for (int i = 0; i < 4; i++)
		if (board[toCheck[i]->location.GetX()][toCheck[i]->location.GetY()] != nullptr)
			return true;
	return false;
}

//turns each falling block in the falling piece into a permanent piece
void Tetris::SetFallingPiece(bool delay) {

	//doesn't do anything until the set delay has been met
	if (delay) {
		framesSinceLastSet++;
		if (framesSinceLastSet < setDelay)
			return;
	}

	framesSinceLastSet = 0;

	for (int i = 0; i < 4; i++)
		SetBlock(Point(fallingPiece[i]->location.GetX(), fallingPiece[i]->location.GetY()), new Block(fallingPiece[i]->color));
	SpawnPiece();

	ClearLines(CheckClearLines());
}

//updates the position of the shadow to be as far down on the board under the falling pieceq
void Tetris::UpdateShadow() {

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
	} while (!CheckBoardCollisionY(tempFalling) && !CheckPieceCollision(tempFalling));

	CopyFalling(fallingPieceShadow, previous);

}

//returns what lines need to be cleared
std::vector<int> Tetris::CheckClearLines() {

	//list of ints to store what lines need to be cleared
	std::vector<int> linesToClear;

	//loops through each column
	for (int line = 0; line < boardHeight; line++) {

		bool full = true;

		//loops through each row and saves if there was a gap
		for (int col = 0; col < boardWidth; col++)
			if (board[col][line] == nullptr)
				full = false;

		//adds this row to the list if it was full
		if (full)
			linesToClear.push_back(line);
	}

	//returns the rows to clear
	return linesToClear;
}

//clears a list of lines
void Tetris::ClearLines(std::vector<int> linesToClear) {

	for (int i = 0; i < linesToClear.size(); i++) {

		int line = linesToClear[i];

		ClearLine(line);

		for (int lineToMove = line - 1; lineToMove >= 0; lineToMove--)
			MoveLine(lineToMove);
	}
}

//clears a line of all its blocks
void Tetris::ClearLine(int line) {

	for (int col = 0; col < boardWidth; col++)
		board[col][line] = nullptr;
}

//moves a line down one line
void Tetris::MoveLine(int line) {

	for (int col = 0; col < boardWidth; col++)
		board[col][line + 1] = board[col][line];

	ClearLine(line);
}

//creates a fresh array of falling piece blocks
std::array<FallingBlock*, 4> Tetris::FreshFalling() {

	std::array<FallingBlock*, 4> tempFalling;

	for (int i = 0; i < 4; i++)
		tempFalling[i] = new FallingBlock(Point(0, 0), GRAY);

	return tempFalling;
}

//returns a copy of the falling piece
void Tetris::CopyFalling(std::array<FallingBlock*, 4> copyTo, std::array<FallingBlock*, 4> copyFrom) {

	for (int i = 0; i < 4; i++) {

		copyTo[i]->location.SetX(copyFrom[i]->location.GetX());
		copyTo[i]->location.SetY(copyFrom[i]->location.GetY());
	}
}