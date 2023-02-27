#include "Tetris.h"
#include "Helper.h"

#include <array>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <functional>


Tetris::Tetris(Point _position) : Process("Tetris", _position, Point(655, 630)) {

	Setup();
}

void Tetris::Setup() {

	won = false;
	lost = false;
	toClear = 20;
	linesLeft = toClear;
	timeSinceLastFrame = 0;
	targetFrameRate = 10;

	dropDelay = 5;
	framesSinceLastDrop = 0;

	setDelay = 3;
	framesSinceLastSet = 0;

	holdAvailable = true;
	hold = NullFalling();

	fallingPiece = FreshFalling();

	ResetBoard();
	GenerateSevenBag();
	SpawnPiece();

	time = 0;
}


void Tetris::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		offset.SetX(offset.GetX() + 5);
		offset.SetY(offset.GetY() + 5);

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << time;
		std::string timeString = stream.str();

		if (GameEnded()) {

			DrawHold(offset);
			offset.SetY(offset.GetY() + 4 * blockSize + 5);
			DrawText("Hold", offset.GetX(), offset.GetY(), 20, BLACK);
			offset.SetY(offset.GetY() - (4 * blockSize + 5));

			offset.SetX(offset.GetX() + 4 * blockSize + 20);
			DrawPieces(offset);
			DrawBoardBoarders(offset);

			offset.SetX(offset.GetX() + boardWidth * blockSize + 20);
			DrawBag(offset);

			offset.SetX(offset.GetX() - (boardWidth * blockSize + 20));
			offset.SetY(offset.GetY() + boardHeight * blockSize + 5);
			DrawText(("Time: " + timeString + "s Lines: " + std::to_string(linesLeft)).c_str(), offset.GetX(), offset.GetY(), 20, BLACK);

		} else if (lost)
			DrawText(("You survived for: " + timeString + " seconds.\nYou had: " + std::to_string(linesLeft) + " lines left to clear\nPress R to restart").c_str(), offset.GetX(), offset.GetY(), 20, RED);

		else if (won)
			DrawText(("You cleared " + std::to_string(toClear) + " in: " + timeString + " seconds.\nPress R to restart").c_str(), offset.GetX(), offset.GetY(), 20, GREEN);

	}
}
void Tetris::DrawHold(Point offset) {

	if (HoldExists()) {
		Point topCorner = GetTopLeftCorner(hold);
		Point bottomCorner = GetBottomRightCorner(hold);

		Point pieceSize = Point((bottomCorner.GetX() - topCorner.GetX()) * blockSize, (bottomCorner.GetY() - topCorner.GetY()) * blockSize);

		Point leeway = Point(((4 * blockSize) - pieceSize.GetX()) / 2, ((4 * blockSize) - pieceSize.GetY()) / 2);

		for (int i = 0; i < 4; i++)
			DrawRectangle(
				offset.GetX() + blockSize * (hold[i]->location.GetX() - topCorner.GetX()) + leeway.GetX(),
				offset.GetY() + blockSize * (hold[i]->location.GetY() - topCorner.GetY()) + leeway.GetY(),
				blockSize, blockSize, hold[i]->color);
	}

	//draws the borders
	DrawLine(offset.GetX(), offset.GetY(), offset.GetX(), offset.GetY() + blockSize * 4, BLACK);
	DrawLine(offset.GetX(), offset.GetY(), offset.GetX() + blockSize * 4, offset.GetY(), BLACK);
	DrawLine(offset.GetX(), offset.GetY() + blockSize * 4, offset.GetX() + blockSize * 4, offset.GetY() + blockSize * 4, BLACK);
	DrawLine(offset.GetX() + blockSize * 4, offset.GetY(), offset.GetX() + blockSize * 4, offset.GetY() + blockSize * 4, BLACK);
}
void Tetris::DrawBoardBoarders(Point offset) {

	//draws all vertical lines
	for (int i = 0; i < boardWidth + 1; i++)
		DrawLine(offset.GetX() + blockSize * i, offset.GetY(), offset.GetX() + blockSize * i, offset.GetY() + boardHeight * blockSize, BLACK);

	//draws all horizontal lines
	for (int i = 0; i < boardHeight + 1; i++)
		DrawLine(offset.GetX(), offset.GetY() + blockSize * i, offset.GetX() + boardWidth * blockSize, offset.GetY() + blockSize * i, BLACK);
}
void Tetris::DrawPieces(Point offset) {

	//loops through the board and draws the piece if there was one
	for (int i = 0; i < boardWidth; i++)
		for (int j = 0; j < boardHeight; j++)
			if (board[i][j] != nullptr)
				DrawRectangle(
					offset.GetX() + blockSize * i,
					offset.GetY() + blockSize * j,
					blockSize, blockSize, board[i][j]->color);

	//draws the shadow
	UpdateShadow();
	for (int i = 0; i < 4; i++)
		DrawRectangle(
			offset.GetX() + blockSize * fallingPieceShadow[i]->location.GetX(),
			offset.GetY() + blockSize * fallingPieceShadow[i]->location.GetY(),
			blockSize, blockSize, fallingPieceShadow[i]->color);

	//draws the falling piece
	for (int i = 0; i < 4; i++)
		DrawRectangle(
			offset.GetX() + blockSize * fallingPiece[i]->location.GetX(),
			offset.GetY() + blockSize * fallingPiece[i]->location.GetY(),
			blockSize, blockSize, fallingPiece[i]->color);
}
void Tetris::DrawBag(Point offset) {

	int piecesToDraw = 5;

	if (pieceBag.size() < 5)
		piecesToDraw = pieceBag.size();

	int bagPieceGap = 1;

	for (int i = 0; i < piecesToDraw; i++) {

		std::array<FallingBlock*, 4> toDraw = pieceBag[i];

		Point topCorner = GetTopLeftCorner(toDraw);
		Point bottomCorner = GetBottomRightCorner(toDraw);
		Point pieceSize = Point((bottomCorner.GetX() - topCorner.GetX()) * blockSize, (bottomCorner.GetY() - topCorner.GetY()) * blockSize);

		Point leeway = Point(((4 * blockSize) - pieceSize.GetX()) / 2, ((4 * blockSize) - pieceSize.GetY()) / 2);

		Point corner = GetTopLeftCorner(toDraw);
		for (int k = 0; k < 4; k++)
			DrawRectangle(
				offset.GetX() + blockSize * (toDraw[k]->location.GetX() - topCorner.GetX()) + leeway.GetX(),
				offset.GetY() + blockSize * (toDraw[k]->location.GetY() - topCorner.GetY()) + leeway.GetY() + 4 * blockSize * i,
				blockSize, blockSize, toDraw[k]->color);

		//draws a line under this bag piece
		DrawLine(offset.GetX(), offset.GetY() + blockSize * 4 * i, offset.GetX() + blockSize * 4, offset.GetY() + blockSize * 4 * i, BLACK);
	}

	Point bagBoardSize = Point();
	bagBoardSize.SetX(4 * blockSize);
	bagBoardSize.SetY(piecesToDraw * 4 * blockSize);

	//draws the borders
	DrawLine(offset.GetX(), offset.GetY(), offset.GetX() + bagBoardSize.GetX(), offset.GetY(), BLACK);
	DrawLine(offset.GetX(), offset.GetY() + bagBoardSize.GetY(), offset.GetX() + bagBoardSize.GetX(), offset.GetY() + bagBoardSize.GetY(), BLACK);
	DrawLine(offset.GetX(), offset.GetY(), offset.GetX(), offset.GetY() + piecesToDraw * blockSize * 4, BLACK);
	DrawLine(offset.GetX() + bagBoardSize.GetX(), offset.GetY(), offset.GetX() + bagBoardSize.GetX(),offset.GetY() + bagBoardSize.GetY(), BLACK);
}

Point Tetris::GetTopLeftCorner(std::array<FallingBlock*, 4> toCheck) {

	Point toReturn = Point(boardWidth, boardHeight);
	for (int i = 0; i < 4; i++) {

		if (toReturn.GetX() > toCheck[i]->location.GetX())
			toReturn.SetX(toCheck[i]->location.GetX());

		if (toReturn.GetY() > toCheck[i]->location.GetY())
			toReturn.SetY(toCheck[i]->location.GetY());
	}

	return toReturn;
}

Point Tetris::GetBottomRightCorner(std::array<FallingBlock*, 4> toCheck) {

	Point toReturn = Point(0, 0);
	for (int i = 0; i < 4; i++) {

		if (toReturn.GetX() < toCheck[i]->location.GetX() + 1)
			toReturn.SetX(toCheck[i]->location.GetX() + 1);

		if (toReturn.GetY() < toCheck[i]->location.GetY() + 1)
			toReturn.SetY(toCheck[i]->location.GetY() + 1);
	}

	return toReturn;
}


void Tetris::OnKeyPress(KeyPress* e) {

	if (display) {

		if (GameEnded()) {

			if (e->GetKeyCode() == KEY_J)
				SlideSpawned(true);
			else if (e->GetKeyCode() == KEY_L)
				SlideSpawned(false);
			else if (e->GetKeyCode() == KEY_K)
				DropSpawned(true);
			else if (e->GetKeyCode() == KEY_SPACE)
				HardDropSpawned();
			else if (e->GetKeyCode() == KEY_I || e->GetKeyCode() == KEY_S)
				RotateSpawned();
			else if (e->GetKeyCode() == KEY_W)
				for (int i = 0; i < 3; i++)
					RotateSpawned();
			else if (e->GetKeyCode() == KEY_D)
				for (int i = 0; i < 2; i++)
					RotateSpawned();
			else if (e->GetKeyCode() == KEY_A)
				SwapWithHold();
		} else {
			if (e->GetKeyCode() == KEY_R) //restart button
				Setup();
		}

	}
}
void Tetris::OnMousePress(MousePress* e, int taskbarHeight) {

	if (display) {

		SuperMousePress(NormaliseMousePos(taskbarHeight));

		Point normalisedMouse = NormaliseMousePos(taskbarHeight + barHeight);
	}
}

void Tetris::Tick(float elapsedTime) {

	if (GameEnded()) {

		//stores how much time has been since the start
		time += elapsedTime;

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
}

//sets all the board spots to null
void Tetris::ResetBoard() {

	for (int i = 0; i < boardWidth; i++)

		for (int j = 0; j < boardHeight; j++)

			board[i][j] = nullptr;

	fallingPieceShadow = FreshFalling();
}

//sets an individual board spot to a block
void Tetris::SetBlock(Point loc, Block* piece) {

	board[loc.GetX()][loc.GetY()] = piece;
}

void Tetris::GenerateSevenBag() {

	//a list of the piece spawn functions
	std::vector<std::function<void(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation)>> SpawnFunctions;
	SpawnFunctions.push_back(std::bind(&Tetris::SpawnTBlock, this, std::placeholders::_1, std::placeholders::_2));
	SpawnFunctions.push_back(std::bind(&Tetris::SpawnLineBlock, this, std::placeholders::_1, std::placeholders::_2));
	SpawnFunctions.push_back(std::bind(&Tetris::SpawnLBlock, this, std::placeholders::_1, std::placeholders::_2));
	SpawnFunctions.push_back(std::bind(&Tetris::SpawnReverseLBlock, this, std::placeholders::_1, std::placeholders::_2));
	SpawnFunctions.push_back(std::bind(&Tetris::SpawnOBlock, this, std::placeholders::_1, std::placeholders::_2));
	SpawnFunctions.push_back(std::bind(&Tetris::SpawnSBlock, this, std::placeholders::_1, std::placeholders::_2));
	SpawnFunctions.push_back(std::bind(&Tetris::SpawnReverseSBlock, this, std::placeholders::_1, std::placeholders::_2));

	//a vector of piece spawn indexes
	std::vector<int> pieceSpawnIndexes;
	for (int i = 0; i < 7; i++)
		pieceSpawnIndexes.push_back(i);

	Point spawnLocation = Point(4, 0);

	//spawns all the piece types into the bag
	while (pieceSpawnIndexes.size() > 0) {

		//gets a random index from list of function indexes to call
		int randomIndex = Helper::Random(0, pieceSpawnIndexes.size() - 1);
		int functionIndex = pieceSpawnIndexes[randomIndex];

		//spawns this piece type into the bag
		std::array<FallingBlock*, 4> newFallingPiece = FreshFalling();
		SpawnFunctions[functionIndex](newFallingPiece, spawnLocation);
		pieceBag.push_back(newFallingPiece);

		//removes this piece spawn option
		pieceSpawnIndexes.erase(pieceSpawnIndexes.begin() + randomIndex);
	}
}


void Tetris::SpawnPiece() {

	if (pieceBag.size() <= 0)
		GenerateSevenBag();

	CopyFallingWithColor(fallingPiece, pieceBag[0]);

	pieceBag.erase(pieceBag.begin());

	lost = CheckLoss();
}
void Tetris::SpawnTBlock(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation) {

	toSpawn[0]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0));
	toSpawn[1]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0));
	toSpawn[2]->location.Set(new Point(spawnLocation.GetX() + 2, spawnLocation.GetY() + 0));
	toSpawn[3]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1));

	SetPieceColor(toSpawn, MAGENTA);
}
void Tetris::SpawnLineBlock(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation) {
	toSpawn[0]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0));
	toSpawn[1]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1));
	toSpawn[2]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 2));
	toSpawn[3]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 3));

	SetPieceColor(toSpawn, SKYBLUE);
}
void Tetris::SpawnLBlock(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation) {
	toSpawn[0]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0));
	toSpawn[1]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1));
	toSpawn[2]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 2));
	toSpawn[3]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 2));

	SetPieceColor(toSpawn, ORANGE);
}
void Tetris::SpawnReverseLBlock(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation) {
	toSpawn[0]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0));
	toSpawn[1]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1));
	toSpawn[2]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 2));
	toSpawn[3]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 2));

	SetPieceColor(toSpawn, DARKBLUE);
}
void Tetris::SpawnOBlock(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation) {
	toSpawn[0]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0));
	toSpawn[1]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1));
	toSpawn[2]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0));
	toSpawn[3]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1));

	SetPieceColor(toSpawn, YELLOW);
}
void Tetris::SpawnSBlock(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation) {

	toSpawn[0]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0));
	toSpawn[1]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1));
	toSpawn[2]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 0));
	toSpawn[3]->location.Set(new Point(spawnLocation.GetX() + 2, spawnLocation.GetY() + 1));

	SetPieceColor(toSpawn, RED);
}
void Tetris::SpawnReverseSBlock(std::array<FallingBlock*, 4> toSpawn, Point spawnLocation) {
	toSpawn[0]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 0));
	toSpawn[1]->location.Set(new Point(spawnLocation.GetX() + 1, spawnLocation.GetY() + 1));
	toSpawn[2]->location.Set(new Point(spawnLocation.GetX() + 0, spawnLocation.GetY() + 1));
	toSpawn[3]->location.Set(new Point(spawnLocation.GetX() + 2, spawnLocation.GetY() + 0));

	SetPieceColor(toSpawn, LIME);
}

void Tetris::SetPieceColor(std::array<FallingBlock*, 4> toSet, Color c) {
	for (int i = 0; i < 4; i++)
		toSet[i]->color = c;
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
		if (toCheck[i]->location.GetY() < 0 || toCheck[i]->location.GetY() > boardHeight - 1)
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

	holdAvailable = true;

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

	UpdateLinesLeft(linesToClear.size());

	for (int i = 0; i < linesToClear.size(); i++) {

		int line = linesToClear[i];

		ClearLine(line);

		for (int lineToMove = line - 1; lineToMove >= 0; lineToMove--)
			MoveLine(lineToMove);
	}

	won = CheckWin();
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

//creates an array of null pointers
std::array<FallingBlock*, 4> Tetris::NullFalling() {

	std::array<FallingBlock*, 4> tempFalling;

	for (int i = 0; i < 4; i++)
		tempFalling[i] = nullptr;

	return tempFalling;
}

//returns a copy of the falling piece
void Tetris::CopyFalling(std::array<FallingBlock*, 4> copyTo, std::array<FallingBlock*, 4> copyFrom) {

	for (int i = 0; i < 4; i++) {

		copyTo[i]->location.SetX(copyFrom[i]->location.GetX());
		copyTo[i]->location.SetY(copyFrom[i]->location.GetY());
	}
}

//returns a copy of the falling piece
void Tetris::CopyFallingWithColor(std::array<FallingBlock*, 4> copyTo, std::array<FallingBlock*, 4> copyFrom) {

	CopyFalling(copyTo, copyFrom);
	for (int i = 0; i < 4; i++)

		copyTo[i]->color = copyFrom[i]->color;
}

//swaps the current falling piece with the hold
void Tetris::SwapWithHold() {

	if (holdAvailable) {

		if (HoldExists()) {

			std::array<FallingBlock*, 4> tempFalling;
			tempFalling = FreshFalling();
			CopyFallingWithColor(tempFalling, hold);
			CopyFallingWithColor(hold, fallingPiece);
			CopyFallingWithColor(fallingPiece, tempFalling);

			PushFallingToStart(fallingPiece);

		} else {

			hold = FreshFalling();
			CopyFallingWithColor(hold, fallingPiece);
			fallingPiece = FreshFalling();
			SpawnPiece();
		}

		holdAvailable = false;

		if (CheckPieceCollision(fallingPiece)) {
			lost = true;
		}
	}
}

//pushes the falling piece to the top of the board
void Tetris::PushFallingToStart(std::array<FallingBlock*, 4> toPush) {

	Point corner = GetTopLeftCorner(toPush);

	for (int i = 0; i < 4; i++) {
		toPush[i]->location.SetY(toPush[i]->location.GetY() - corner.GetY());
		toPush[i]->location.SetX(toPush[i]->location.GetX() - corner.GetX() + 4);
	}
}


void Tetris::UpdateLinesLeft(int linesCleared) {
	linesLeft -= linesCleared;
}

bool Tetris::CheckWin() {
	return linesLeft <= 0;
}

bool Tetris::CheckLoss() {
	return CheckPieceCollision(fallingPiece);
}