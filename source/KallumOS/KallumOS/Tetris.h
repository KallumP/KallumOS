#pragma once
#include "Process.h"
#include <array>
#include <vector>


struct Block {

	Block() {

	}
	Block(Color col) {
		color = col;
	}

	Color color;
};


struct FallingBlock : public Block {

	Point location;

	FallingBlock(Point loc, Color col) : Block(col) {
		location = loc;
	}

};



class Tetris : public Process {

public:
	Tetris();
	Tetris(Point _position, Point _size);

	void Draw(Point offset);
	void OnKeyPress(KeyPress* e);
	void OnMousePress(MousePress* e, int taskbarHeight);
	void Tick(float elapsedTime);

private:

	void Setup();

	void DrawBoardBoarders(Point offset);
	void DrawPieces(Point offset);
	void DrawHold(Point offset);

	void ResetBoard();
	void SpawnPiece();

	void SetBlock(Point loc, Block* piece);


	static const int boardWidth = 10;
	static const int boardHeight = 20;
	static const int pieceSize = 30;

	std::array<std::array<Block*, boardHeight>, boardWidth> board;
	std::array<FallingBlock*, 4> fallingPiece;
	std::array<FallingBlock*, 4> fallingPieceShadow;
	std::array<FallingBlock*, 4> hold;

	float time;
	int toClear;
	int linesLeft;
	bool won;
	bool lost;

	double timeSinceLastFrame;
	int targetFrameRate;

	int dropDelay;
	int framesSinceLastDrop;

	bool softSet;
	int setDelay;
	int framesSinceLastSet;

	int holdAvailable;


	void SwapWithHold();
	bool HoldExists() { return hold[0] != nullptr; }
	bool GameEnded() { return !lost && !won; }
	void PushFallingToStart(std::array<FallingBlock*, 4> toPush);

	Point GetTopCorner(std::array<FallingBlock*, 4> toCheck);

	void DropSpawned(bool softDrop);
	void SlideSpawned(bool left);
	void HardDropSpawned();
	void RotateSpawned();
	void ShiftSpawned(std::array<FallingBlock*, 4> toMove, int left, int right, int down, int up);
	void UpdateShadow();
	std::vector<int> CheckClearLines();
	void ClearLines(std::vector<int> toClear);
	void ClearLine(int line);
	void MoveLine(int line);

	bool CheckBoardCollisionX(std::array<FallingBlock*, 4> toCheck);
	bool CheckBoardCollisionY(std::array<FallingBlock*, 4> toCheck);
	bool CheckPieceCollision(std::array<FallingBlock*, 4> toCheck);

	void SetFallingPiece(bool delay);

	void SpawnTBlock(Point spawnLocation);
	void SpawnLBlock(Point spawnLocation);
	void SpawnSBlock(Point spawnLocation);
	void SpawnOBlock(Point spawnLocation);

	void SpawnReverseLBlock(Point spawnLocation);
	void SpawnReverseSBlock(Point spawnLocation);

	void SpawnLineBlock(Point spawnLocation);

	std::array<FallingBlock*, 4> FreshFalling();
	std::array<FallingBlock*, 4> NullFalling();
	void CopyFalling(std::array<FallingBlock*, 4> copyTo, std::array<FallingBlock*, 4> copyFrom);
	void CopyFallingWithColor(std::array<FallingBlock*, 4> copyTo, std::array<FallingBlock*, 4> copyFrom);

	void UpdateLinesLeft(int linesCleared);
	bool CheckWin();
	bool CheckLoss();
};



