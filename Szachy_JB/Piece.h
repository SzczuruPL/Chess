#pragma once
#include "Player.h"
#include "Square.h"
#include "Constants.h"
#include <iostream>
#include <vector>

class Board;

//enum short
//{
//	BLACK, WHITE
//};

//git testv 2 

class Piece
{
protected:
	bool isCaptured;
	short color;
	Board* board;
	//void move();
	//void caputure();
	char sign;
	int x, y;
public:
	Piece(short color);
	void print();
	short getcolorPiece();
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	char getSign();
	void setBoard(Board* board);
	virtual std::vector <std::pair <int, int> > getMoves(bool captureMove) = 0;
	virtual bool move(int x, int y, int x1, int y1) = 0;
	virtual bool capture(int x, int y, int x1, int y1) = 0;
};

class Pawn :public Piece
{
public:
	Pawn(short color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Knight :public Piece
{
public:
	Knight(short color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Rook :public Piece
{
private:
	bool moved;
public:
	Rook(short color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool wasMoved();
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Bishop :public Piece
{
public:
	Bishop(short color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class King :public Piece
{
private:
	bool moved;
	bool castle(int x, int y, int x1, int y1);
public:
	King(short color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	//    bool isChecked;
	bool wasMoved();
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Queen :public Piece
{
public:
	Queen(short color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
