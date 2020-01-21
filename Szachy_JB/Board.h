#pragma once
#include "Player.h"
#include "Piece.h"
#include "Square.h"
#include "Constants.h"
#include <iostream>

class Board
{
	Square arr[8][8];
public:
	Board();
	void setpiece(Piece* piece, int j, int i);
	bool isempty(int x, int y);
	Color getcolorBoard(int x, int y);
	bool forcedMove(int x, int y, int x1, int y1);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
	void print();
};

