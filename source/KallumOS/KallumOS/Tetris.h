#pragma once
#include "Process.h"
#include <array>


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

	void DrawBoardBoarders(Point offset);
	void DrawPieces(Point offset);

	void ResetBoard();
	void SpawnPiece();


	void SetPiece(Point loc, Block* piece);


	static const int boardWidth = 10;
	static const int boardHeight = 20;
	static const int pieceSize = 30;

	std::array<std::array<Block*, boardHeight>, boardWidth> board;

	std::array<FallingBlock*, 4> fallingPiece;


	int framesPerDrop;
	int framesTillNextDrop;

	void DropSpawned();
	void SlideSpawned(bool left);
	void HardDropSpawned();
	void ShiftSpawned(std::array<FallingBlock*, 4> toMove, int left, int right, int down, int up);
	bool CheckCollisionX(std::array<FallingBlock*, 4> toCheck);
	bool CheckCollisionY(std::array<FallingBlock*, 4> toCheck);
	void SetFallingPiece();

	double timeSinceLastFrame;
	int targetFrameRate;

	void SpawnTBlock(Point spawnLocation);
	void SpawnLBlock(Point spawnLocation);
	void SpawnSBlock(Point spawnLocation);

	void SpawnReverseLBlock(Point spawnLocation);
	void SpawnReverseSBlock(Point spawnLocation);

	void SpawnLineBlock(Point spawnLocation);
	void SpawnOBlock(Point spawnLocation);

	std::array<FallingBlock*, 4> FreshFalling();
	void CopyFalling(std::array<FallingBlock*, 4> copyTo, std::array<FallingBlock*, 4> copyFrom);
};



