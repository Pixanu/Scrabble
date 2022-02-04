//#include "pch.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <conio.h>
#include <random>
#include <ctime>

#define MAX_BOARD 15

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int currentScore = 0,
numbersFromBoard[15],
board[15][15] =
{
		{5,1,1,2,1,1,1,5,1,1,1,2,1,1,5},
		{1,4,1,1,1,3,1,1,1,3,1,1,1,4,1},
		{1,1,4,1,1,1,2,1,2,1,1,1,4,1,1},
		{2,1,1,4,1,1,1,2,1,1,1,4,1,1,2},
		{1,1,1,1,4,1,1,1,1,1,4,1,1,1,1},
		{1,3,1,1,1,3,1,1,1,3,1,1,1,3,1},
		{1,1,2,1,1,1,2,1,2,1,1,1,2,1,1},
		{5,1,1,2,1,1,1,5,1,1,1,2,1,1,5},
		{1,1,2,1,1,1,2,1,2,1,1,1,2,1,1},
		{1,3,1,1,1,3,1,1,1,3,1,1,1,3,1},
		{1,1,1,1,4,1,1,1,1,1,4,1,1,1,1},
		{2,1,1,4,1,1,1,2,1,1,1,4,1,1,2},
		{1,1,4,1,1,1,2,1,2,1,1,1,4,1,1},
		{1,4,1,1,1,3,1,1,1,3,1,1,1,4,1},
		{5,1,1,2,1,1,1,5,1,1,1,2,1,1,5}
};

int checkWord(string word_chosen)
{
	for (int charIndex = 0; charIndex < word_chosen.length(); ++charIndex) {
		if (isupper(word_chosen[charIndex]))
			return 1;
		if (isdigit(word_chosen[charIndex]))
			return 2;
		if (!isalpha(word_chosen[charIndex]))
			return 3;
	}
	return 0;
}

//FILTERS
bool Checking(string line)
{
	if (all_of(line.begin(), line.end(), &::islower)) //checks if the characters are lowercase
	{
		if (all_of(line.begin(), line.end(), &::isdigit)) //checks if the characters is a decimal degit character
			return false;
		else
			if (all_of(line.begin(), line.end(), &::isalpha)) //checks if it is an alphabetic letter
				return true;
		return false;
	}
	/*if (orientation = "Horizontal" && boardColumn + line.length() > 15)
	{

	}

	if (orientation = "Vertical" && boardLine + line.length() > 15)
	{

	}*/

	return false;
}
//Score Calculator
int ScoreCalculator(const string& line)
{
	int scoreline = 0;
	map <char, int> alphabet;

	alphabet['a'] = 1;
	alphabet['e'] = 1;
	alphabet['i'] = 1;
	alphabet['o'] = 1;
	alphabet['u'] = 1;
	alphabet['l'] = 1;
	alphabet['n'] = 1;
	alphabet['s'] = 1;
	alphabet['t'] = 1;
	alphabet['r'] = 1;

	alphabet['d'] = 2;
	alphabet['g'] = 2;

	alphabet['b'] = 3;
	alphabet['c'] = 3;
	alphabet['m'] = 3;
	alphabet['p'] = 3;

	alphabet['f'] = 4;
	alphabet['h'] = 4;
	alphabet['v'] = 4;
	alphabet['w'] = 4;
	alphabet['y'] = 4;

	alphabet['k'] = 5;

	alphabet['j'] = 8;
	alphabet['x'] = 8;

	alphabet['q'] = 10;
	alphabet['z'] = 10;

	for (int i = 0; i < line.length(); i++)
		scoreline += alphabet[line[i]];

	return scoreline;
}

void calculateScore(string word_chosen, int numbersFromBoardReplacedWithChars[15])
{
	int letterScore = 0;
	int tripleWord = 0;
	int doubleWord = 0;
	map<char, int> alphabet;

	alphabet['a'] = 1;
	alphabet['e'] = 1;
	alphabet['i'] = 1;
	alphabet['o'] = 1;
	alphabet['u'] = 1;
	alphabet['l'] = 1;
	alphabet['n'] = 1;
	alphabet['s'] = 1;
	alphabet['t'] = 1;
	alphabet['r'] = 1;

	alphabet['d'] = 2;
	alphabet['g'] = 2;

	alphabet['b'] = 3;
	alphabet['c'] = 3;
	alphabet['m'] = 3;
	alphabet['p'] = 3;

	alphabet['f'] = 4;
	alphabet['h'] = 4;
	alphabet['v'] = 4;
	alphabet['w'] = 4;
	alphabet['y'] = 4;

	alphabet['k'] = 5;

	alphabet['j'] = 8;
	alphabet['x'] = 8;

	alphabet['q'] = 10;
	alphabet['z'] = 10;

	//First// we go through each character of each word
	for (int indexWord = 0; indexWord < word_chosen.length(); ++indexWord)
	{
		//Second// we go through the mapping
		for (map<char, int>::iterator it = alphabet.begin(); it != alphabet.end(); ++it)
		{
			//checks every iteration from the mapping with the word character
			if (it->first == word_chosen[indexWord])
			{
				letterScore = it->second;
				switch (numbersFromBoardReplacedWithChars[indexWord])
				{
				case 1:
					currentScore += letterScore;
					break;
				case 2:
					currentScore += letterScore * 2;
					break;
				case 3:
					currentScore += letterScore * 3;
					break;
				case 4:
					currentScore += letterScore;
					doubleWord++;
					break;
				case 5:
					currentScore += letterScore;
					tripleWord++;
					break;
				default:
					currentScore += 0;
					break;
				}
			}
		}
	}

	if (tripleWord)
		currentScore *= (tripleWord * 3);
	if (doubleWord)
		currentScore *= (doubleWord * 2);
}
//Board Function
void Board(string orientation, string word_chosen, int selectedLine, int selectedColumn)
{
	// Board Display
	int arrIndex = 0;
	for (int boardLine = 0; boardLine < MAX_BOARD; ++boardLine)
	{
		cout << endl;
		for (int boardColumn = 0; boardColumn < MAX_BOARD; ++boardColumn)
		{
			if (orientation == "Horizontal")
			{
				// white color
				SetConsoleTextAttribute(h, 0x007 | 0x0008);

				// if not in the word interval --- we are printing the board
				if (!(selectedLine - 1 == boardLine && boardColumn >= selectedColumn - 1 && selectedColumn - 1 <= boardColumn))
					cout << board[boardLine][boardColumn] << ' ';

				// checks if we are at the collum and the row that we selected
				if (boardLine == selectedLine - 1 && boardColumn == selectedColumn - 1)
				{
					// red color
					SetConsoleTextAttribute(h, 0x004 | 0x0008);
					// displaying the word
					for (int wordIndex = 0; wordIndex < word_chosen.length(); ++wordIndex) {
						cout << word_chosen[wordIndex] << ' ';
						// putting in the array the numbers that were replaced by the letters
						numbersFromBoard[arrIndex] = board[boardLine][boardColumn + arrIndex];
						arrIndex++;
					}
					// white color
					SetConsoleTextAttribute(h, 0x007 | 0x0008);
					// displaying the rest of the numbers after the word
					for (int m = selectedColumn - 1 + word_chosen.length(); m < MAX_BOARD; ++m) {
						cout << board[boardLine][m] << ' ';
					}
				}
			}

			if (orientation == "Vertical")
			{
				// white color
				SetConsoleTextAttribute(h, 0x007 | 0x0008);
				if ((boardLine >= selectedLine - 1 && boardLine < word_chosen.length() + selectedLine) && boardColumn == selectedColumn - 1)
				{
					// white color
					SetConsoleTextAttribute(h, 0x007 | 0x0008);

					if (arrIndex < word_chosen.length())
					{
						// red color
						SetConsoleTextAttribute(h, 0x004 | 0x0008);
						cout << word_chosen[arrIndex] << ' ';
						numbersFromBoard[arrIndex] = board[boardLine][boardColumn];
						arrIndex++;
					}
					else
						cout << board[boardLine][boardColumn] << ' ';
				}
				else
					cout << board[boardLine][boardColumn] << ' ';
			}
		}
	}
}

/*This Class was suppose to hand in the player 7 tiles from a random tile "bag" and with those 7 tiles the player was suppose to create a word.
Each tile has a chance and was suppose to use a randomizer function to hand in the player the tiles.
The tiles had to be taken from an array/tuple.Inside the "bag" were a diiferent number of tiles,so for each character lets say A we  would have a different numbers of tiles based on the assessment brift for the charater A there will be 9 tiles.


/*class Hand_Tile { public:


		void call_random(char orig[15][15]);
		char letter1[7]; //letter1 is the buffer for the user tile/characters

		int j[7];
		int leng1;

		static char alpha[100];
		static int chance;


		Hand_Tile()
		{
			leng1 = 0;


		}


};*/



/*void Hand_Tile::call_random(char orig[15][15])
{
	int itr;
	randomize();
	for (itr = 0; itr < 7; itr++)
	{
		j[itr] = random(chance);                     //randomly gives 7 tiles/characters to a user
		letter1[itr] = alpha[j[itr]];
		leng1++;

	}




}*/


int main()
{
	//void Hand_Tile;
	int selectColumn,
		selectLine;

	vector<tuple<string, int>> my_arr;

	ifstream dict_file("Word.txt");

	string line;
	string word_chosen;
	string selectOrientation;


	while (getline(dict_file, line))
	{
		if (Checking(line) == true)
		{
			my_arr.push_back(make_tuple(line, ScoreCalculator(line)));
			/*for (const auto&i : my_arr)
			{
				cout << get<0>(i) << " " << get<1>(i) << "\n";
			}*/
		}
	}

	do
	{
		cout << "Choose word: ";
		cin >> word_chosen;

		switch (checkWord(word_chosen))
		{
		case 1:
			cout << "The word needs to be lowercase" << endl;
			break;
		case 2:
			cout << "The word is NOT suppose to contain any numbers" << endl;
			break;
		case 3:
			cout << "The word only needs to have letters from the alphabet---no symbols" << endl;
			break;
		default:
			break;
		}
	} while (checkWord(word_chosen) != 0);

	do
	{
		cout << "Choose a column between 1-15: ";
		cin >> selectColumn;
	} while (selectColumn < 1 && selectColumn > MAX_BOARD);

	do
	{
		cout << "Choose a row between 1-15: ";
		cin >> selectLine;
	} while (selectLine < 1 && selectLine > MAX_BOARD);

	do
	{
		cout << "Select orientation-----Vertical or Horizontal: ";
		cin >> selectOrientation;
	} while (selectOrientation != "Horizontal" && selectOrientation != "Vertical");
	Board(selectOrientation, word_chosen, selectLine, selectColumn);

	calculateScore(word_chosen, numbersFromBoard);

	cout << endl;
	cout << "\nYour word score is: " << currentScore;

	_getch();
}
