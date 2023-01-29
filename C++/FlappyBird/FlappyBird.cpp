#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

bool isPlaying = true;
bool isDead = false;
bool isStarted = false;
bool jumped = false;

int height = 16;
int width = 32;

int scorePoint;
int score;


int x = 5;
int y = 8;

int k = 0;

string GameOver[9] = { "G","A","M","E"," ","O","V","E","R" };

string obstacle[16];
int globalObstaclePos =width;


void Restart() {
	score = 0;
	y = 8;
	globalObstaclePos = width;
	isDead = false;
	isStarted = false;
	isPlaying = true;
}

void ObstacleCalc() {
	srand(time(0));
	scorePoint = rand() % (height-5) + 5;
	for (int i = 0; i <= height; i++)
	{
			if (i>scorePoint-3&&i<scorePoint+3)
			{
				obstacle[i] = " ";
				continue;
			}
			obstacle[i] = "#";
	}
}
void Logic() {
	if (isPlaying)
	{
		Sleep(100);
		if (_kbhit())
		{
			if (_getch() == 32)
			{
				y -= 2;
				isStarted = true;
			}
		}
		if (!isStarted)
		{
			ObstacleCalc();
		}
		if (isStarted)
		{
			globalObstaclePos--;
			y++;
			if (globalObstaclePos == 0)
			{
				ObstacleCalc();
				globalObstaclePos = width;
			}
			if (x == globalObstaclePos)
			{
				if (y < scorePoint - 3 || y > scorePoint + 3)
				{
					isPlaying = false;
				}
				else {
					score++;
				}
			}
			if (y == 0 || y == height)
			{
				isPlaying = false;
			}
		}
	}
}

void Art() {
	system("cls");
	if (!isPlaying)
	{
		cout << "  GAME OVER    SCORE: " << score<<endl;
	}
	else {
		cout << "      SCORE: " << score << endl;

	}
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (i == 0 || i == height || j == 0 || j == width)
			{
				cout << "#";
				continue;
			}
			if (i == y && j == x)
			{
				cout << "O";
				continue;
			}
			if (j == globalObstaclePos || j == globalObstaclePos+1)
			{
				cout << obstacle[i];
				continue;
			}
			cout << " ";
		}
		cout << endl;
	}
	if (!isPlaying)
	{
		cout << "Restart? ";
		system("pause");
		Restart();
	}
	else {
		cout << "       FLAPPY BIRD";
	}
}







int main() {
	ObstacleCalc();
	while (!isDead)
	{
		Art();
		Logic();
	}
}