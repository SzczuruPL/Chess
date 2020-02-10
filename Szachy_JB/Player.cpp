#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include "Constants.h"
#include <iostream>
#include <vector>

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
	else if (color != board->getcolorBoard(x, y))
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
	else if (board->getcolorBoard(x1, y1) != board->getcolorBoard(x, y))
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
	else if (color != board->getcolorBoard(x, y))
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
	else if (board->getcolorBoard(x1, y1) != board->getcolorBoard(x, y))
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
