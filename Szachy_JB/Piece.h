#pragma once
#include "Player.h"
#include "Square.h"
#include "Constants.h"
#include <iostream>
#include <vector>

//enum Color
//{
//	BLACK, WHITE
//};
class Board;

//git testv 2 

class Piece
{
protected:
	bool isCaptured;
	Color color;
	Board* board;
	//void move();
	//void caputure();
	char sign;
	int x, y;
public:
	Piece(Color color);
	void print();
	Color getcolorPiece();
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
	Pawn(Color color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Knight :public Piece
{
public:
	Knight(Color color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Rook :public Piece
{
private:
	bool moved;
public:
	Rook(Color color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool wasMoved();
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Bishop :public Piece
{
public:
	Bishop(Color color);
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
	King(Color color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	//    bool isChecked;
	bool wasMoved();
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
class Queen :public Piece
{
public:
	Queen(Color color);
	std::vector <std::pair <int, int> > getMoves(bool captureMove);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
};
