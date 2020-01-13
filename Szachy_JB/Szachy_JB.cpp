#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <fstream>
#include <cstdlib>
//
void p(std::string s) {
	std::cout << s << std::endl;
}




bool SILENT = 0;
//using namespace std;
enum Color
{
	BLACK, WHITE
};
class Board;
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
	Color getcolor();
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
class Square
{
	int x;
	int y;
	Piece* piece;
public:
	Square();
	void setpiece(Piece* piece);
	bool isempty();
	Color getcolor();
	Piece* getpiece();
	bool move(int x1, int y1);
	bool capture(int x1, int y1);
	void setCorPiece(int x, int y);
	void setcor(int x, int y);
	void print();
};
class Board
{
	Square arr[8][8];
public:
	Board();
	void setpiece(Piece* piece, int j, int i);
	bool isempty(int x, int y);
	Color getcolor(int x, int y);
	bool forcedMove(int x, int y, int x1, int y1);
	bool move(int x, int y, int x1, int y1);
	bool capture(int x, int y, int x1, int y1);
	void print();
};
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
//void Piece::move()
//{}
//void Piece::caputure()
//{}
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
Color Piece::getcolor()
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
Color Square::getcolor()
{
	return piece->getcolor();
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
Color Board::getcolor(int x, int y)
{
	return arr[x][y].getcolor();
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
Player::Player(Color color, Board* board)
{
	this->board = board;
	this->color = color;
	for (int i = 0; i < 8; i++)
	{
		Piece* pawn = new Pawn(color);
		pieces.push_back(pawn);
	}
	for (int i = 0; i < 8; i++)
	{
		if (color == WHITE)
		{
			board->setpiece(pieces.at(i), 6, i);
			pieces.at(i)->setX(6);
			pieces.at(i)->setY(i);
		}
		else
		{
			board->setpiece(pieces.at(i), 1, i);
			pieces.at(i)->setX(1);
			pieces.at(i)->setY(i);
		}
	}
	Piece* rook = new Rook(color);
	pieces.push_back(rook);
	Piece* knight = new Knight(color);
	pieces.push_back(knight);
	Piece* bishop = new Bishop(color);
	pieces.push_back(bishop);
	Piece* queen = new Queen(color);
	pieces.push_back(queen);
	Piece* king = new King(color);
	pieces.push_back(king);
	Piece* bishop1 = new Bishop(color);
	pieces.push_back(bishop1);
	Piece* knight1 = new Knight(color);
	pieces.push_back(knight1);
	Piece* rook1 = new Rook(color);
	pieces.push_back(rook1);
	for (int i = 8; i < 16; i++)
	{
		if (color == WHITE)
		{
			board->setpiece(pieces.at(i), 7, i - 8);
			pieces.at(i)->setX(7);
			pieces.at(i)->setY(i - 8);
		}
		else
		{
			board->setpiece(pieces.at(i), 0, i - 8);
			pieces.at(i)->setX(0);
			pieces.at(i)->setY(i - 8);
		}
	}
	for (int i = 0; i < 16; i++)
	{
		pieces.at(i)->setBoard(board);
	}
}
std::vector <Piece*> Player::getPieces()
{
	return pieces;
}
bool Player::isNoMove()
{
	bool captureMove = 0;
	for (int i = 0; i < 16; i++)
	{
		std::vector <std::pair<int, int> > v = pieces[i]->getMoves(0);
		int x, y, x1, y1;
		x = pieces[i]->getX();
		y = pieces[i]->getY();
		for (int j = 0; j < v.size(); j++)
		{
			x1 = v[j].first;
			y1 = v[j].second;
		}   //TODO
		//std::cout << x << "," << y << " - " << x1 << "," << y1 << std::endl;
		if (checkMove(x, y, x1, y1, captureMove))
		{
			return false;
		}
	}
	return true;
}
//Piece* Player::getPawn()
//{
//
//}
char Player::getPawnY(char x1, char y1)
{
	if (color == WHITE)
	{
		for (int i = 0; i < 8; i++)
		{
			//std::cout << pieces.at(i)->getX() << pieces.at(i)->getY() << '-' << x1 << y1 << std::endl;
			if (pieces.at(i)->getY() + 'A' == x1 and (56 - pieces.at(i)->getX() == y1 - 1 or 56 - pieces.at(i)->getX() == y1 - 2))
			{
				return 56 - pieces.at(i)->getX();
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (pieces.at(i)->getY() + 'A' == x1 and (56 - pieces.at(i)->getX() == y1 + 1 or 56 - pieces.at(i)->getX() == y1 + 2))
			{
				return 56 - pieces.at(i)->getX();
			}
		}
	}
}
char Player::getKnightY(bool pos)
{
	if (color == BLACK)
	{
		pos = !pos;
	}
	//std::cout << "Yoohoo" << pos << ' ' << pieces.at(9)->getX() << ' ' << pieces.at(14)->getX() << std::endl;
	if (pos == 1)
	{
		return 56 - pieces.at(9)->getX();
	}
	else
	{
		return 56 - pieces.at(14)->getX();
	}
}
char Player::getKnightX(bool pos)
{
	if (color == BLACK)
	{
		pos = !pos;
	}
	if (pos == 1)
	{
		return pieces.at(9)->getY() + 'A';
	}
	else
	{
		return pieces.at(14)->getY() + 'A';
	}
}
char Player::getRookY(bool pos)
{
	if (pos == 1)
	{
		return 56 - pieces.at(8)->getX();
	}
	else
	{
		return 56 - pieces.at(15)->getX();
	}
}
char Player::getRookX(bool pos)
{
	if (pos == 1)
	{
		return pieces.at(8)->getY() + 'A';
	}
	else
	{
		return pieces.at(15)->getY() + 'A';
	}
}
char Player::getBishopY(bool pos)
{
	if (pos == 1)
	{
		return 56 - pieces.at(10)->getX();
	}
	else
	{
		return 56 - pieces.at(13)->getX();
	}
}
char Player::getBishopX(bool pos)
{
	if (pos == 1)
	{
		return pieces.at(10)->getY() + 'A';
	}
	else
	{
		return pieces.at(13)->getY() + 'A';
	}
}
char Player::getQueenY()
{
	return 56 - pieces.at(11)->getX();
}
char Player::getQueenX()
{
	return pieces.at(11)->getY() + 'A';
}
char Player::getKingY()
{
	return 56 - pieces.at(12)->getX();
}
char Player::getKingX()
{
	return pieces.at(12)->getY() + 'A';
}
Piece* Player::getKing()
{
	return pieces.at(12);
}
bool Player::isChecked()
{
	SILENT = 1;
	std::vector <Piece*> temp = opponent->getPieces();
	for (int i = 0; i < 16; i++)
	{
		int x, y, x1, y1;
		//std::cout << temp[i] << std::endl;
		x = temp[i]->getX();
		y = temp[i]->getY();
		x1 = getKing()->getX();
		y1 = getKing()->getY();
		//std::cout << char(y+65} << x+1 << '-' << char(y1+65} << x1+1 << std::endl;
		//std::cout << "Silent is:" << SILENT << std::endl;
		if (temp[i]->capture(x, y, x1, y1)) //silent
		{
			SILENT = 0;
			return true;
		}
	}
	SILENT = 0;
	return false;
}
void Player::setOpponent(Player* opponent)
{
	this->opponent = opponent;
}
void Player::print()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces.at(i)->print();
	}
	std::cout << std::endl;
}
bool Player::forcedMove(int x, int y, int x1, int y1)
{
	//std::cout << "Forced move: " << x <<','<<y<<'-'<<x1<<','<<y1<<std::endl;
	return board->forcedMove(x, y, x1, y1);
}
bool Player::checkMove(int x, int y, int x1, int y1, bool captureMove)
{
	//board->print();
	if (board->isempty(x, y))
	{
		//std::cout << "Square is empty!" << std::endl;
		return false;
	}
	else if (x > 7 or x < 0 or y>7 or y < 0 or x1>7 or x1 < 0 or y1>7 or y1 < 0)
	{
		//std::cout << "halo" << std::endl;
		return false;
	}
	else if (color != board->getcolor(x, y))
	{
		//std::cout << "Chosen piece belongs to opponent!" << std::endl;
		return false;
	}
	else if (board->isempty(x1, y1) and !captureMove)
	{
		std::cout << x << ',' << y << " , " << x1 << ',' << y1 << std::endl;
		bool rtn = board->move(x, y, x1, y1);
		if (rtn == 1 and isChecked())
		{
			//std::cout << "return false" << std::endl;
			//std::cout << "forcedmove call isChecked" << std::endl;
			forcedMove(x1, y1, x, y);
			//std::cout << "King is still beeing checked!" << std::endl;
			return false;
		}
		else if (rtn == 1)
		{
			//std::cout << "return rtn" << rtn << std::endl;
			//std::cout << "forcedmove call isChecked" << std::endl;
			forcedMove(x1, y1, x, y);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (board->getcolor(x1, y1) != board->getcolor(x, y))
	{
		SILENT = 1;
		bool rtn = board->capture(x, y, x1, y1);
		if (rtn)
			forcedMove(x1, y1, x, y); //przy takiej konstrukcji zniknie zbijana figurka
		return rtn;
		SILENT = 0;
	}
	else
	{
		//std::cout << "Square is already ocuppied!" << std::endl;
		return false;
	}
}
bool Player::move(int x, int y, int x1, int y1)
{
	if (board->isempty(x, y))
	{
		if (!SILENT)
			std::cout << "Square is empty!" << std::endl;
		return false;
	}
	else if (x > 7 or x < 0 or y>7 or y < 0 or x1>7 or x1 < 0 or y1>7 or y1 < 0)
	{
		if (!SILENT)
			std::cout << "Square out of range!" << std::endl;
		return false;
	}
	else if (color != board->getcolor(x, y))
	{
		if (!SILENT)
			std::cout << "Chosen piece belongs to opponent!" << std::endl;
		return false;
	}
	else if (board->isempty(x1, y1))
	{
		bool rtn = board->move(x, y, x1, y1);
		if (rtn == 1 and isChecked())
		{
			forcedMove(x1, y1, x, y);
			if (!SILENT)
				std::cout << "King is still beeing checked!" << std::endl;
			return false;
		}
		else
			return rtn;
	}
	else if (board->getcolor(x1, y1) != board->getcolor(x, y))
	{
		return board->capture(x, y, x1, y1);
	}
	else
	{
		if (!SILENT)
			std::cout << "Square is already ocuppied!" << std::endl;
		return false;
	}
}
/// -wczytywanie-
struct moveStruct
{
	char x;
	char y;
	char x1;
	char y1;
};
struct moveConv
{
	int x;
	int y;
	int x1;
	int y1;
};
void structConv(moveStruct str, moveConv& strc)
{
	//std::cout << str.x << str.y << ' ' << str.x1 << str.y1 << std::endl;
	strc.x = str.x - 'A';
	strc.x1 = str.x1 - 'A';
	strc.y = 8 - (str.y - '0');
	strc.y1 = 8 - (str.y1 - '0');
	//std::cout << strc.x << '-' << strc.y << ' ' << strc.x1 << '-' << strc.y1 << std::endl;
}
moveStruct move(std::string token, Color color, Player player)
{
	moveStruct ret;
	std::cout << token << ' ' << color << std::endl;
	char x, x1, y, y1;
	bool capture = 0;
	int l = token.size();
	if (token[l - 1] == '+')
	{
		token = token.substr(0, l - 1);
		std::cout << "Readmove->Check" << std::endl;
	}
	if (token == "O-O-O")
	{
		//if (color == WHITE)
		//{
			//king
			//x='E'
			//y=1
			//x1='C'
			//y1=1
			//rook
			//x='A'
			//y=1
			//x1='D'
			//y=1
		//}
		//else
		//{
			//king
			//x='E'
			//y=8
			//x1='C'
			//y1=8
			//rook
			//x='A'
			//y=8
			//x1='D'
			//y=8
		//}
		std::cout << "Readmove->CastlingLong" << std::endl;
	}
	else if (token == "O-O")
	{
		//if (color == WHITE)
		//{
			//king
			//x='E'
			//y=1
			//x1='G'
			//y1=1
			//rook
			//x='H'
			//y=1
			//x1='F'
			//y=1
		//}
		//else
		//{
			//king
			//x='E'
			//y=8
			//x1='G'
			//y1=8
			//rook
			//x='H'
			//y=8
			//x1='F'
			//y=8
		//}
		std::cout << "Readmove->CastlingShort" << std::endl;
	}
	else if (token[1] == 'x')
	{
		capture = 1;
		token = token.substr(0, 1) + token.substr(2, 2);
		std::cout << "Readmove->Capture" << std::endl;
	}
	if (token[0] >= 'A' and token[0] <= 'Z')
	{
		char figure = token[0];
		token.substr(1, 2);
		if (figure == 'R')
		{
			if (token[1] >= 'a' && token[1] <= 'h' && token[2] >= 'a' && token[2] <= 'h')
			{
				x = token[1] - 32;
				x1 = token[2] - 32;
				y1 = token[3];
				if (player.getRookY(0) == y1)
				{
					ret.x = x;
					ret.y = player.getRookY(0);
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = x;
					ret.y = player.getRookY(1);
					ret.x1 = x1;
					ret.y1 = y1;

				}
			}
			else if (token[1] >= '1' && token[1] <= '8')
			{
				y = token[1];
				x1 = token[2] - 32;
				y1 = token[3];
				if (player.getRookX(0) == x1)
				{
					ret.x = player.getRookX(0);
					ret.y = y;
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = player.getRookX(1);
					ret.y = y;
					ret.x1 = x1;
					ret.y1 = y1;
				}
			}
			else
			{
				x1 = token[1] - 32;
				y1 = token[2];
				if (player.getRookX(0) == x1 or player.getRookY(0) == y1)
				{
					ret.x = player.getRookX(0);
					ret.y = player.getRookY(0);
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = player.getRookX(1);
					ret.y = player.getRookY(1);
					ret.x1 = x1;
					ret.y1 = y1;
				}
			}
		}
		else if (figure == 'B')
		{
			if (token[1] >= 'a' && token[1] <= 'h' && token[2] >= 'a' && token[2] <= 'h') //to jest okej
			{
				x = token[1] - 32;
				x1 = token[2] - 32;
				y1 = token[3];
				if (player.getBishopY(0) == y1)
				{
					ret.x = x;
					ret.y = player.getBishopY(0);
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = x;
					ret.y = player.getBishopY(1);
					ret.x1 = x1;
					ret.y1 = y1;

				}
			}
			else if (token[1] >= '1' && token[1] <= '8') // to te¿
			{
				y = token[1];
				x1 = token[2] - 32;
				y1 = token[3];
				if (player.getBishopX(0) == x1)
				{
					ret.x = player.getBishopX(0);
					ret.y = y;
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = player.getBishopX(1);
					ret.y = y;
					ret.x1 = x1;
					ret.y1 = y1;
				}
			}
			else
			{
				x1 = token[1] - 32;
				y1 = token[2];
				if (player.getBishopX(0) + player.getBishopY(0) == x1 + y1 or player.getBishopX(0) - player.getBishopY(0) == x1 - y1)
				{
					ret.x = player.getBishopX(0);
					ret.y = player.getBishopY(0);
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = player.getBishopX(1);
					ret.y = player.getBishopY(1);
					ret.x1 = x1;
					ret.y1 = y1;
				}
			}
		}
		else if (figure == 'N')
		{
			if (token[1] >= 'a' && token[1] <= 'h' && token[2] >= 'a' && token[2] <= 'h')
			{
				x = token[1] - 32;
				x1 = token[2] - 32;
				y1 = token[3];
				if (player.getKnightY(0) == y1)
				{
					//std::cout << "Knight0" << std::endl;
					ret.x = x;
					ret.y = player.getKnightY(0);
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{

					ret.x = x;
					ret.y = player.getKnightY(1);
					ret.x1 = x1;
					ret.y1 = y1;
					std::cout << ret.x << ret.y << std::endl;

				}
			}
			else if (token[1] >= '1' && token[1] <= '8') // to tez
			{
				y = token[1];
				x1 = token[2] - 32;
				y1 = token[3];
				if (player.getKnightX(0) == x1)
				{
					ret.x = player.getKnightX(0);
					ret.y = y;
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = player.getKnightX(1);
					ret.y = y;
					ret.x1 = x1;
					ret.y1 = y1;
				}
			}
			else
			{
				x1 = token[1] - 32;
				y1 = token[2];
				if ((player.getKnightX(0) - x1) * (player.getKnightX(0) - x1) + (player.getKnightY(0) - y1) * (player.getKnightY(0) - y1) == 5)
				{
					ret.x = player.getKnightX(0);
					ret.y = player.getKnightY(0);
					ret.x1 = x1;
					ret.y1 = y1;
				}
				else
				{
					ret.x = player.getKnightX(1);
					ret.y = player.getKnightY(1);
					ret.x1 = x1;
					ret.y1 = y1;
				}
			}
		}
		else if (figure == 'Q')
		{
			x1 = token[1] - 32;
			y1 = token[2];
			ret.x = player.getQueenX();
			ret.y = player.getQueenY();
			ret.x1 = x1;
			ret.y1 = y1;
		}
		else if (figure == 'K')
		{
			x1 = token[1] - 32;
			y1 = token[2];
			ret.x = player.getKingX();
			ret.y = player.getKingY();
			ret.x1 = x1;
			ret.y1 = y1;
		}
		else
		{
			std::cout << "Co chlop z figura robi" << std::endl;
		}
	}
	else
	{
		if (capture == 1)
		{
			x = token[0] - 32;
			x1 = token[1] - 32;
			y1 = token[2];
			if (color == WHITE)
				y = token[2] - 1;
			else
				y = token[2] + 1;
			ret.x = x;
			ret.y = y;
			ret.x1 = x1;
			ret.y1 = y1;
		}
		else
		{
			x = token[0] - 32;
			x1 = token[0] - 32;
			y1 = token[1];
			y = player.getPawnY(x1, y1);
			ret.x = x;
			ret.y = y;
			ret.x1 = x1;
			ret.y1 = y1;
			//std::cout << x << y << '-' << x1 << y1 << std::endl;
			//std::cout << "Readmove->Pawn" << std::endl;
		}
	}
	return ret;
}
void sim(Player& white_player, Player& black_player, Board& board)
{
	std::ifstream inFile;
	inFile.open("test3.txt");

	if (!inFile.good())
	{
		std::cerr << "unable to open file";
		return;
	}
	while (!inFile.eof())
	{
		std::string num, white, black;
		inFile >> num >> white >> black;
		if (num == "1-0" or num == "1/2-1/2" or num == "0-1")
			break;
		moveConv strc;
		moveStruct str = move(white, WHITE, white_player);
		structConv(str, strc);
		//std::cout << strc.x << strc.y << ' ' << strc.x1 << strc.y1 << std::endl;
		white_player.forcedMove(strc.y, strc.x, strc.y1, strc.x1);
		board.print();
		if (black == "1-0" or black == "1/2-1/2" or black == "0-1")
			break;
		str = move(black, BLACK, black_player);
		structConv(str, strc);
		black_player.forcedMove(strc.y, strc.x, strc.y1, strc.x1);
		board.print();
	}

	inFile.close();
}
int main()
{/*
	p("main");*/
	int x, y, x1, y1;
	char cy, cy1;
	Board board;
	Player white(WHITE, &board);
	Player black(BLACK, &board);
	white.setOpponent(&black);
	black.setOpponent(&white);
	srand(time(0));
	bool test = 0;
	sim(white, black, board);
	//            white.move(6,1,4,1);
	//            white.move(6,2,4,2);
	//            white.move(6,3,4,3);
	//            white.move(7,1,5,2);
	//            white.move(7,2,5,0);
	//            white.move(7,3,5,3);
	//white.forcedMove(6,5,5,5);
	//black.forcedMove(1,4,2,3);
	//white.forcedMove(6,6,4,6);
	//black.forcedMove(0,3,4,7);

	//            black.forcedMove(0,4,2,4);
	//            white.forcedMove(7,3,5,3);
	//    board.print();
	//    std::cout << "AreWeChecking:" << black.isChecked() << std::endl;
	//    std::cout << "isOurKingChecked:" << white.isChecked() << std::endl;
	//    while(1)
	////    while(true)
	//    {
	//        if(!white.isNoMove())
	//        {
	//            do
	//            {
	//                //SILENT=1;
	//                std::cout << "Player White: " << std::endl;
	//                //x=rand()%8;
	//                //y=rand()%8;
	//                //x1=rand()%8;
	//                //y1=rand()%8;
	//                std::cin >> cy >> x >> cy1 >> x1;
	//                y=(int)cy-65; y1=(int)cy1-65;
	//                test=white.move(x-1,y,x1-1,y1);
	//                if(test)
	//                {
	//                    board.print();
	//                    std::cout << "AreWeChecking:" << white.isChecked() << std::endl;
	//                    std::cout << "isOurKingChecked:" << black.isChecked() << std::endl;
	//                   Sleep(500);
	//                }
	//            }
	//            while(!test);
	//        }
	//        else
	//        {
	//            if(white.isChecked())
	//            {
	//                std::cout << "Winner is BLACK!" << std::endl;
	//                return 0;
	//            }
	//            else
	//            {
	//                std::cout << "Stalemate!" << std::endl;
	//                return 0;
	//            }
	//        }
	//        if(!black.isNoMove())
	//        {
	//            do
	//            {
	//                //SILENT=1;
	//                std::cout << "Player Black: " << std::endl;
	//                //x=rand()%8;
	//                //y=rand()%8;
	//                //x1=rand()%8;
	//                //y1=rand()%8;
	//				std::cin >> cy >> x >> cy1 >> x1;
	//                y=(int)cy-65; y1=(int)cy1-65;
	//                test=black.move(x-1,y,x1-1,y1);
	//                if(test)
	//                {
	//                    board.print();
	//                    std::cout << "AreWeChecking:" << black.isChecked() << std::endl;
	//                    std::cout << "isOurKingChecked:" << white.isChecked() << std::endl;
	//					Sleep(500);
	//                }
	//            }
	//            while(!test);
	//        }
	//        else
	//        {
	//            if(black.isChecked())
	//            {
	//                std::cout << "Winner is WHITE!" << std::endl;
	//                return 0;
	//            }
	//            else
	//            {
	//                std::cout << "Stalemate!" << std::endl;
	//                return 0;
	//            }
	//        }
	//    }
	return 0;
}
