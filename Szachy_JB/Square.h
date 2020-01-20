#pragma once
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Constants.h"
#include <iostream>
#include <vector>

class Piece;
//enum short;
class Square
{
	int x;
	int y;
	Piece* piece;
public:
	Square();
	void setpiece(Piece* piece);
	bool isempty();
	short getcolorSquare();
	Piece* getpiece();
	bool move(int x1, int y1);
	bool capture(int x1, int y1);
	void setCorPiece(int x, int y);
	void setcor(int x, int y);
	void print();
};