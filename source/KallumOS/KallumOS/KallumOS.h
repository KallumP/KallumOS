
#pragma once
#include "olcPixelGameEngine.h"

class KallumOS : olc::PixelGameEngine {

public:

	KallumOS();

	void Tick(olc::PixelGameEngine*, float);

	void Draw(olc::PixelGameEngine*);

	~KallumOS();

};