#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include "Constants.h"
#include <iostream>

Square::Square()
{
	piece = NULL;
}
void Square::setpiece(Piece* piece)
{
	this->piece = piece;
}
bool Square::isempty()
{
	return piece == NULL;
}
Color Square::getcolorSquare()
{
	return piece->getcolorPiece();
}
Piece* Square::getpiece()
{
	return piece;
}
bool Square::move(int x1, int y1)
{
	if (piece == NULL)
		return false;
	else
		return piece->move(x, y, x1, y1);
}
bool Square::capture(int x1, int y1)
{
	return piece->capture(x, y, x1, y1);
}
void Square::setCorPiece(int x, int y)
{
	piece->setX(x);
	piece->setY(y);
}
void Square::setcor(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Square::print()
{
	if (piece != NULL)
	{
		piece->print();
	}
	else
	{
		if ((x + y) % 2 == 0)
			std::cout << (char)178 << (char)178;
		else
			std::cout << (char)176 << (char)176;
	}
}
