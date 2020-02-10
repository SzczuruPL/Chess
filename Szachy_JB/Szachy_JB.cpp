#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <fstream>
#include <cstdlib>
#include "Temp.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Square.h"
#include "Constants.h"

//using namespace std;

//void Piece::move()
//{}
//void Piece::caputure()
//{}

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
		//if (color == Col::WHITE)
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
		//if (color == Col::WHITE)
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
	inFile.open("C:\\Users\\Arkadiusz\\source\\repos\\Chess\\test3.txt");

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
		std::cout << num << std::endl;
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
bool SILENT;
//Color BLACK;
//Color WHITE;

int main()
{/*
	p("main");*/
	SILENT = 0;
	//WHITE = 0;
	//BLACK= 1;


	Temp temp;
	temp.print();
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
	//                std::cout << "Winner is Col::BLACK!" << std::endl;
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
	//                std::cout << "Winner is Col::WHITE!" << std::endl;
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
