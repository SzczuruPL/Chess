#include <iostream>
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include "Constants.h"


Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arr[i][j].setcor(i, j);
		}
	}
}
void Board::setpiece(Piece* piece, int j, int i)
{
	arr[j][i].setpiece(piece);
}
bool Board::isempty(int x, int y)
{
	return arr[x][y].isempty();
}
Color Board::getcolorBoard(int x, int y)
{
	return arr[x][y].getcolorSquare();
}

bool Board::forcedMove(int x, int y, int x1, int y1)
{
	//std::cout << arr[x][y].getpiece()->getSign() << ": " << char(y+65} << x+1 << '-' << char(y1+65} << x1+1 << std::endl;
	arr[x1][y1].setpiece(arr[x][y].getpiece());
	arr[x1][y1].setCorPiece(x1, y1);
	arr[x][y].setpiece(NULL);

	return true;
}
bool Board::move(int x, int y, int x1, int y1)
{
	if (arr[x][y].move(x1, y1))
	{

		std::cout << arr[x][y].getpiece()->getSign() << ": " << char(y + 65) << 8 - x << '-' << char(y1 + 65) << 8 - x1 << std::endl;
		arr[x1][y1].setpiece(arr[x][y].getpiece());
		arr[x1][y1].setCorPiece(x1, y1);
		arr[x][y].setpiece(NULL);
		return true;
	}
	else
		return false;
}
bool Board::capture(int x, int y, int x1, int y1)
{
	if (arr[x][y].capture(x1, y1))
	{
		std::cout << arr[x][y].getpiece()->getSign() << "x: " << char(y + 65) << 8 - x << '-' << char(y1 + 65) << 8 - x1 << std::endl;
		//Sleep(2500);
		arr[x1][y1].setpiece(arr[x][y].getpiece());
		arr[x1][y1].setCorPiece(x1, y1);
		arr[x][y].setpiece(NULL);
		return true;
	}
	else
		return false;
}
void Board::print()
{
	std::cout << " ";
	for (int i = 0; i < 8; i++)
	{
		std::cout << " " << char(i + 65);
	}
	std::cout << " " << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << 8 - i << " ";
		for (int j = 0; j < 8; j++)
		{
			arr[i][j].print();
		}
		std::cout << " " << 8 - i << std::endl;
	}
	std::cout << " ";
	for (int i = 0; i < 8; i++)
	{
		std::cout << " " << char(i + 65);
	}
	std::cout << std::endl;
}