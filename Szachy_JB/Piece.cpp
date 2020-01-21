#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include "Constants.h"
#include <iostream>
#include <vector>

Piece::Piece(Color color)
{
	this->color = color;
}
void Piece::print()
{
	if (color == BLACK)
		std::cout << 'B' << sign;
	else
		std::cout << 'W' << sign;
}
Color Piece::getcolorPiece()
{
	return color;
}
void Piece::setX(int x)
{
	this->x = x;
}
void Piece::setY(int y)
{
	this->y = y;
}
int Piece::getX()
{
	return x;
}
int Piece::getY()
{
	return y;
}
char Piece::getSign()
{
	return sign;
}
void Piece::setBoard(Board* board)
{
	this->board = board;
}
Pawn::Pawn(Color color) :Piece(color)
{
	sign = 'P';
}
std::vector <std::pair <int, int> > Pawn::getMoves(bool captureMove)
{
	std::vector <std::pair<int, int> > v;
	if (color == WHITE)
	{
		if (!captureMove)
		{
			v.push_back(std::make_pair(x - 1, y));
			if (x == 6)
				v.push_back(std::make_pair(x - 2, y));

		}
		else
		{
			v.push_back(std::make_pair(x - 1, y + 1));
			v.push_back(std::make_pair(x - 1, y - 1));
		}
	}
	else
	{
		if (!captureMove)
		{
			v.push_back(std::make_pair(x + 1, y));
			if (x == 1)
				v.push_back(std::make_pair(x + 2, y));

		}
		else
		{
			v.push_back(std::make_pair(x + 1, y + 1));
			v.push_back(std::make_pair(x + 1, y - 1));
		}
	}
	return v;
}
bool Pawn::move(int x, int y, int x1, int y1)
{
	if (color == WHITE)
	{
		if (y == y1 and (x == 6))
		{
			if (x - x1 == 2)
			{
				if (board->isempty(x - 1, y))
					return true;
				else
				{
					if (!SILENT)
					{
						std::cout << "Pawn: Jumping over ocuppied square!" << std::endl;
					}
					return false;
				}
			}
			else if (x - x1 == 1)
			{
				return true;
			}
			else
			{
				if (!SILENT)
				{
					std::cout << "Pawn: Illegal move!" << std::endl;
				}
				return false;
			}
		}
		else
		{
			if (x - x1 == 1 and y == y1)
			{
				return true;
			}
			else
			{

				if (!SILENT)
				{
					std::cout << "Pawn: Illegal move!" << std::endl;
				}
				return false;
			}
		}
	}
	else
	{
		if (y == y1 and (x == 1))
		{
			if (x - x1 == -2 or x - x1 == -1)
			{
				return true;
			}
			else
			{

				if (!SILENT)
				{
					std::cout << "Pawn: Illegal move!" << std::endl;
				}
				return false;
			}
		}
		else
		{
			if (x - x1 == -1 and y == y1)
			{
				return true;
			}
			else
			{
				if (!SILENT)
				{
					std::cout << "Pawn: Illegal move!" << std::endl;
				}
				return false;
			}
		}
	}
}
bool Pawn::capture(int x, int y, int x1, int y1)
{
	if (color == WHITE)
	{
		if (x > x1 and (x - x1)* (x - x1) + (y - y1) * (y - y1) == 2)
		{
			return true;
		}
		else
		{

			if (!SILENT)
			{
				std::cout << "Pawn: Illegal move!" << SILENT << std::endl;
			}
			return false;
		}
	}
	else
	{
		if (x < x1 and (x - x1) * (x - x1) + (y - y1) * (y - y1) == 2)
		{
			return true;
		}
		else
		{

			if (!SILENT)
			{
				std::cout << "Pawn: Illegal move!" << std::endl;
			}
			return false;
		}
	}
}
Knight::Knight(Color color) :Piece(color)
{
	sign = 'N';
}
std::vector <std::pair <int, int> > Knight::getMoves(bool captureMove = 1)
{
	std::vector <std::pair<int, int> > v;
	v.push_back(std::make_pair(x - 1, y + 2));
	v.push_back(std::make_pair(x + 1, y + 2));
	v.push_back(std::make_pair(x + 2, y - 1));
	v.push_back(std::make_pair(x + 2, y + 1));
	v.push_back(std::make_pair(x - 2, y - 1));
	v.push_back(std::make_pair(x - 2, y + 1));
	v.push_back(std::make_pair(x - 1, y - 2));
	v.push_back(std::make_pair(x + 1, y - 2));
	return v;
}
bool Knight::move(int x, int y, int x1, int y1)
{
	if ((x - x1) * (x - x1) + (y - y1) * (y - y1) == 5)
	{
		return true;
	}
	else
	{

		if (!SILENT)
		{
			std::cout << "Knight: Illegal move!" << std::endl;
		}
		return false;
	}
}
bool Knight::capture(int x, int y, int x1, int y1)
{
	return move(x, y, x1, y1);
}
Rook::Rook(Color color) :Piece(color)
{
	moved = false;
	sign = 'R';
}
std::vector <std::pair <int, int> >Rook::getMoves(bool captureMove = 1)
{
	std::vector <std::pair<int, int> > v;
	for (int i = 0; i < 8; i++)
	{
		if (i != x)
			v.push_back(std::make_pair(i, y));
		if (i != y)
			v.push_back(std::make_pair(x, i));
	}
	return v;
}
bool Rook::wasMoved()
{
	return moved;
}
bool Rook::move(int x, int y, int x1, int y1)
{
	/// nie potrzebne ale moze byc do roszady
	//    if(!board->isempty(x1,y1))
	//    {
	//        if(!SILENT)
	//        {
	//            std::cout << "Rook: Moving to ocuppied square!" << std::endl;
	//        }
	//        return false;
	//    }
	if (y == y1)
	{
		if (x > x1)
		{
			int temp = x;
			x = x1;
			x1 = temp;
		}
		for (x++; x < x1; x++)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
				{
					std::cout << "Rook: Jumping over ocuppied square!" << std::endl;
				}
				return false;
			}
		}
		moved = true;
		return true;
	}
	else if (x == x1)
	{
		if (y > y1)
		{
			int temp = y;
			y = y1;
			y1 = temp;
		}
		for (y++; y < y1; y++)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
				{
					std::cout << "Rook: Jumping over ocuppied square!" << std::endl;
				}
				return false;
			}
		}
		moved = true;
		return true;
	}
	else
	{

		if (!SILENT)
		{
			std::cout << "Rook: Illegal move!" << std::endl;
		}
		return false;
	}
}
bool Rook::capture(int x, int y, int x1, int y1)
{
	return move(x, y, x1, y1);
}
Bishop::Bishop(Color color) :Piece(color)
{
	sign = 'B';
}
std::vector <std::pair <int, int> > Bishop::getMoves(bool captureMove)
{
	std::vector <std::pair<int, int> > v;
	for (int i = 1; x - i >= 0 and y - i >= 0; i++)
		v.push_back(std::make_pair(x - i, y - i));
	for (int i = 1; x + i != 8 and x + i != 8; i++)
		v.push_back(std::make_pair(x + i, y + i));
	for (int i = 1; x - i >= 0 and y + i != 8; i++)
		v.push_back(std::make_pair(x - i, y + i));
	for (int i = 1; x + i != 8 and y - i >= 0; i++)
		v.push_back(std::make_pair(x + i, y - i));
	return v;
}
bool Bishop::move(int x, int y, int x1, int y1)
{
	if (x - x1 == y - y1)
	{
		if (x > x1) //and y>y1
		{
			int temp = x;
			x = x1;
			x1 = temp;

			temp = y;
			y = y1;
			y1 = temp;
		}
		for (x++, y++; x < x1; x++, y++)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
				{
					std::cout << "Bishop: Jumping over ocuppied square!" << std::endl;
				}
				return false;
			}
		}
		return true;
	}
	else if (x - x1 == -(y - y1))
	{
		if (x > x1) //and y>y1
		{
			int temp = x;
			x = x1;
			x1 = temp;

			temp = y;
			y = y1;
			y1 = temp;
		}
		for (x++, y--; x < x1; x++, y--)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
					std::cout << "Bishop: Jumping over ocuppied square!" << std::endl;
				return false;
			}
		}
		return true;
	}
	else
	{
		if (!SILENT)
			std::cout << "Bishop: Illegal move!" << std::endl;
		return false;
	}

}
bool Bishop::capture(int x, int y, int x1, int y1)
{
	return move(x, y, x1, y1);

}
King::King(Color color) :Piece(color)
{
	moved = false;
	sign = 'K';
}
std::vector <std::pair <int, int> > King::getMoves(bool captureMove = 1)
{
	std::vector <std::pair<int, int> > v;
	v.push_back(std::make_pair(x + 1, y + 1));
	v.push_back(std::make_pair(x - 1, y + 1));
	v.push_back(std::make_pair(x + 1, y - 1));
	v.push_back(std::make_pair(x - 1, y - 1));
	v.push_back(std::make_pair(x + 1, y));
	v.push_back(std::make_pair(x - 1, y));
	v.push_back(std::make_pair(x, y + 1));
	v.push_back(std::make_pair(x, y - 1));
	return v;
}
//bool King::isChecked()
//{
//
//}
bool King::castle(int x, int y, int x1, int y1)
{
	if (wasMoved())
		return false;
	else if ((x == 7 && y == 4 && x1 == 7 && y1 == 2) and board->move(7, 0, 7, 3))
		return true;
	else if ((x == 7 && y == 4 && x1 == 7 && y1 == 6) and board->move(7, 7, 7, 5))
		return true;
	else if ((x == 0 && y == 4 && x1 == 0 && y1 == 2) and board->move(0, 0, 0, 3))
		return true;
	else if ((x == 0 && y == 4 && x1 == 0 && y1 == 2) and board->move(0, 7, 0, 5))
		return true;
	else
		return false;
	//if(Rook->wasMoved())
}
bool King::wasMoved()
{
	return moved;
}
bool King::move(int x, int y, int x1, int y1)
{
	if ((y - y1) * (y - y1) == 4)
	{
		bool cast = castle(x, y, x1, y1);
		if (cast)
			moved = true;
		return cast;
	}
	else if ((x - x1) * (x - x1) + (y - y1) * (y - y1) <= 2)
	{
		moved = true;
		return true;
	}
	else
	{
		if (!SILENT)
			std::cout << "King: Illegal move!" << std::endl;
		return false;
	}
}
bool King::capture(int x, int y, int x1, int y1)
{
	return move(x, y, x1, y1);
}
Queen::Queen(Color color) :Piece(color)
{
	sign = 'Q';
}
std::vector <std::pair <int, int> > Queen::getMoves(bool captureMove = 1)
{
	std::vector <std::pair<int, int> > v;
	for (int i = 0; i < 8; i++)
	{
		if (i != x)
			v.push_back(std::make_pair(i, y));
		if (i != y)
			v.push_back(std::make_pair(x, i));
	}
	for (int i = 1; x - i >= 0 and y - i >= 0; i++)
		v.push_back(std::make_pair(x - i, y - i));
	for (int i = 1; x + i != 8 and x + i != 8; i++)
		v.push_back(std::make_pair(x + i, y + i));
	for (int i = 1; x - i >= 0 and y + i != 8; i++)
		v.push_back(std::make_pair(x - i, y + i));
	for (int i = 1; x + i != 8 and y - i >= 0; i++)
		v.push_back(std::make_pair(x + i, y - i));
	return v;
}
//bool isNoMove();
//bool isChecked();
bool Queen::move(int x, int y, int x1, int y1)
{
	if (x - x1 == y - y1)
	{
		if (x > x1) //and y>y1
		{
			int temp = x;
			x = x1;
			x1 = temp;

			temp = y;
			y = y1;
			y1 = temp;
		}
		for (x++, y++; x < x1; x++, y++)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
					std::cout << "Queen: Jumping over ocuppied square!" << std::endl;
				return false;
			}
		}
		return true;
	}
	else if (x - x1 == -(y - y1))
	{
		if (x > x1) //and y>y1
		{
			int temp = x;
			x = x1;
			x1 = temp;

			temp = y;
			y = y1;
			y1 = temp;
		}
		for (x++, y--; x < x1; x++, y--)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
					std::cout << "Queen: Jumping over ocuppied square!" << std::endl;
				return false;
			}
		}
		return true;
	}
	else if (y == y1)
	{
		if (x > x1)
		{
			int temp = x;
			x = x1;
			x1 = temp;
		}
		for (x++; x < x1; x++)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
					std::cout << "Queen: Jumping over ocuppied square!" << std::endl;
				return false;
			}
		}
		return true;
	}
	else if (x == x1)
	{
		if (y > y1)
		{
			int temp = y;
			y = y1;
			y1 = temp;
		}
		for (y++; y < y1; y++)
		{
			if (!board->isempty(x, y))
			{
				if (!SILENT)
					std::cout << "Queen: Jumping over ocuppied square!" << std::endl;
				return false;
			}
		}
		return true;
	}
	else
	{
		if (!SILENT)
			std::cout << "Queen: Illegal move!" << std::endl;
		return false;
	}

}
bool Queen::capture(int x, int y, int x1, int y1)
{
	return move(x, y, x1, y1);
}