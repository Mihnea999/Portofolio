#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

bool firstRound = true;
bool isPlaying = true;
bool isStarted;

int height = 12;
int width = 64;

int scorePlayer, scoreBot;

int ballPosX = width/2, ballPosY = height/2;
int ballDirX, ballDirY;
int n,m;

int playerY = height/2, botY = height/2;
int playerX = 3, botX = width - playerX;

void ChangeDir() {
	srand(time(0));

	n = rand() % 2;
	m = rand() % 2;
	if (m == 0)
	{
		if (n == 0)
		{
			ballDirY = -1;
		}
		else 
		{
			ballDirY = 1;
		}
	}
	else
	{
		ballDirY = 0;
	}
	if (firstRound)
	{
		firstRound = false;
		n = rand() % 2;
		if (n == 0) {
			ballDirX = -1;
		}
		else 
		{
			ballDirX = 1;
		}
	}

}
void RestartTable() {
	ballDirX = -ballDirX;
	ChangeDir();
	ballPosX = width / 2;
	ballPosY = height / 2;


}
void Logic() {
	Sleep(30);
	if (ballPosY == 0 || ballPosY == height)
	{
		ballDirY = -ballDirY;
	}
	if (ballPosY == playerY &&( ballPosX == playerX+1 || ballPosX == playerX))
	{
		ballDirX = -ballDirX;
		ChangeDir();
	}
	if (ballPosY == botY && (ballPosX == botX || ballPosX == botX+1))
	{
		ballDirX = -ballDirX;
		ChangeDir();
	}
	if (ballPosX == 0)
	{
		scoreBot++;
		RestartTable();
	}
	else if (ballPosX == width) {
		scorePlayer++;
		RestartTable();
	}
	ballPosX += ballDirX;
	ballPosY += ballDirY;
	if (ballDirX > 0) {
		botY = ballPosY;

	}
	if (_kbhit()){
		switch (_getch())
		{
		case 119:
			if (playerY > 1)
			{
				playerY--;
			}
			break;
		case 115:
			if (playerY < height - 1)
			{
				playerY++;
			}
			break;
		default:
			break;
		}
	}
}

void Art() {
	system("Cls");

	cout <<"    " << scorePlayer <<  "                        PONG"<<"                           "<<scoreBot << endl;
	//cout <<"    " << ballDirY <<  "                        PONG"<<"                           "<<ballPosY << endl;
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (i == 0 || i == height)
			{
				cout << "-";
				continue;
			}
			if(j == 0 || j == width)
			{
				cout << "!";
				continue;
			}
			if (i == ballPosY && j == ballPosX)
			{
				cout << "o";
				continue;
			}
			if (j == width / 2)
			{
				cout << ".";
				continue;
			}
			if (j == playerX && i == playerY) {
				cout << "|";
				continue;
			}
			if (j == botX && i == botY) {
				cout << "|";
				continue;
			}
			cout << " ";
		}
		cout << endl;
	}
}



int main() {
	ChangeDir();
	while (isPlaying) {
		Art();
		Logic();
	}
}

