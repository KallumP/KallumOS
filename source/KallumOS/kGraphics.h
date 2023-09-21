#pragma once
#include "raylib.h"
#include <string>


namespace kGraphics {

	static void DrawRect(int x, int y, int width, int height, Color color) {
		DrawRectangleLines(x, y, width, height, color);
	}

	static void FillRect(int x, int y, int width, int height, Color color) {
		DrawRectangle(x, y, width, height, color);
	}

	static void DrawString(std::string toDraw, int x, int y, int fontSize, Color color) {
		DrawText(toDraw.c_str(), x, y, fontSize, color);
	}

	static void kDrawLine(int x, int y, int x2, int y2, Color color) {
		DrawLine(x, y, x2, y2, color);
	}
};