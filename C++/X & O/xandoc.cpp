#include <iostream>
#include <stdlib.h>
using namespace std;

string is = "x";
string winner;
int score = 0;
bool isPlaying = true;
bool xTurn;
int c, r;


string table[3][3]{
	{" "," "," "},
	{" "," "," "},
	{" "," "," "}
};
void Restart() {
	for (int i = 0; i < 3; i++)
	{
		for (int x = 0; x < 3; x++)
		{
			table[i][x] = " ";
		}
	}
	isPlaying = true;
	score = 0;
	winner = " ";
	is = "x";
}

void printWinner() {
	system("cls");
	for (int i = 0; i < 3; i++)
	{
		for (int x = 0; x < 3; x++)
		{
			table[i][x] = " ";
		}
	}
	table[0][1] = winner;
	table[1][0] = "W";
	table[1][1] = "I";
	table[1][2] = "N";
	cout << "     X & O" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << " -------------" << endl;
		for (int x = 0; x < 3; x++)
		{
			cout << " | " << table[i][x];
		}
		cout << " |" << endl;
	}
	cout << " -------------";
	cout << endl << "Restart? ";
	system("pause");
	Restart();

}

void CheckWin() {
	for (int i = 0; i < 3; i++)
	{
		score = 0;
		for (int x = 0; x < 3; x++)
		{
			if (table[i][x] == "x") {
				score += 1;
			}
			if (table[i][x] == "o")
			{
				score += 4;
			}
			if (score == 3)
			{
				winner = "x";
				isPlaying = false;
				printWinner();
			}else if (score == 12)
			{
				winner = "o";
				isPlaying = false;
				printWinner();
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (table[0][0] == is)
		{
			if (table[1][1] == is)
			{
				if (table[2][2] == is)
				{
					winner = is;
					isPlaying = false;
					printWinner();
				}
			}
		}
		is = "o";
	}
	for (int i = 0; i < 2; i++)
	{
		if (table[2][0] == is)
		{
			if (table[1][1] == is)
			{
				if (table[0][2] == is)
				{
					winner = is;
					isPlaying = false;
					printWinner();
				}
			}
		}
		is = "o";
	}
	for (int i = 0; i < 3; i++)
	{
		score = 0;
		for (int x = 0; x < 3; x++)
		{
			if (table[x][i] == "x") {
				score += 1;
			}
			if (table[x][i] == "o")
			{
				score += 4;
			}
			if (score == 3)
			{
				winner = "x";
				isPlaying = false;
				printWinner();
			}
			else if (score == 12)
			{
				winner = "o";
				isPlaying = false;
				printWinner();
			}
		}
	}
}

void printTable() {
	system("cls");
	cout << "     X & O" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << " -------------" << endl;
		for (int x = 0; x < 3; x++)
		{
			cout << " | " << table[i][x];
		}
		cout << " |" << endl;
	}
	cout << " -------------";
}
void AddSimbol() {
	if (table[r - 1][c - 1] != " ") {
		return;
	}
	if (xTurn)
	{
		table[r - 1][c - 1] = "x";
		xTurn = !xTurn;
		return;
	}
	else if (!xTurn)
	{
		table[r - 1][c - 1] = "o";
		xTurn = !xTurn;
	}
}

void SetSimbol() {
	cout << endl  << endl << "      1-3" << endl;
	cout << endl << "Row: ";
	cin >> r;
	cout << endl << "Collum: ";
	cin >> c;
	if (c > 3 || r > 3) {
		return;
	}
	AddSimbol();
}

int main() {
	while (isPlaying)
	{
		printTable();
		SetSimbol();
		CheckWin();
	}
	return 0;
}
