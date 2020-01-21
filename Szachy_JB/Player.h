#pragma once
#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include "Constants.h"
#include <iostream>
#include <vector>

class Player
{
	Color color;
	Board* board;
	Player* opponent;
	std::vector <Piece*> pieces;
public:
	Player(Color color, Board* board);
	std::vector <Piece*> getPieces();
	Piece* getKing();
	char getPawnY(char x1, char y1);
	char getKnightX(bool pos);
	char getKnightY(bool pos);
	char getRookX(bool pos);
	char getRookY(bool pos);
	char getBishopX(bool pos);
	char getBishopY(bool pos);
	char getQueenX();
	char getQueenY();
	char getKingY();
	char getKingX();
	void setOpponent(Player* opponent);
	bool isNoMove();
	bool isChecked();
	void print();
	bool forcedMove(int x, int y, int x1, int y1);
	bool checkMove(int x, int y, int x1, int y1, bool captureMove);
	bool move(int x, int y, int x1, int y1);
};
