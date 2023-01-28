#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
//#include <unistd.h>
using namespace std;

enum Direction{None,UP,DOWN,LEFT,RIGHT};
Direction dir = None;
bool isPlaying = true;
int width = 24;
int height = 16;
int score;
int x = width/2;
int y = height/2;

int k = 0;

int tailX[100], tailY[100], nTail = 5;

int fX = 12;
int fY = 10;
string GameOver[9] = { "G","A","M","E"," ","O","V","E","R" };


char KeyBoard() {
    char c;
    // Set the terminal to raw mode
    while (1) {
        system("stty raw");
        c = getchar();
        // terminate when "." is pressed
        system("stty cooked");
        system("clear");
        if (c == 'p') {
            system("stty cooked");
            exit(0);
        }
        return c;
    }
}
void SpawnFruit()
{
    fX = rand() % (height-1) + 1;
    fY = rand() % (width-1) + 1;
}
void DisplayGameOver() 
{
    int StartPosX = (width/2)-4, StartPosY = height/4;
    system("cls");
    isPlaying = false;
    cout << "             SCORE:" << score << endl;
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (j == 0 || j == width || i == 0 || i == height)
            {
                cout << "#";
                continue;
            }
            if (j == StartPosX && i == StartPosY && k < 9)
            {
                cout << GameOver[k];
                k++;
                StartPosX++;
                continue;
            }
            cout << " ";
        }
        cout << endl;
    }
}
void DisplayBoard() {
    int checker = 0;
    if (dir == UP || dir == DOWN)
    {
        Sleep(130);
    }
    else
    {
        Sleep(40);
    }
    system("cls");
    cout << "             SCORE:" << score << endl;
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            bool DrowTail = false;
            if (j == 0 || j == width || i == 0 || i == height)
            {
                cout << "#";
                continue;
            }
            if (i == y && j == x) {
                cout << "O";
                continue;
            }
            if (i == fX && j == fY)
            {
                cout << "X";
                continue;
            }
            for (int k = 0; k < nTail; k++)
            {
                if (i == tailY[k] && j == tailX[k]) {
                    cout << "o";
                    DrowTail = true;
                }
            }
            if (y == fX && x == fY)
            {
                score++;
                nTail++;
                SpawnFruit();
            }
            if (!DrowTail) {
                cout << " ";
            }
            checker++;
        }
        cout << endl;
    }

}
void Move() {
    int prevX = tailX[0];
    int prevY = tailX[0];

    tailX[0] = x;
    tailY[0] = y;

    int prev2X, prev2Y;

    for (int i = 0; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (y == 0 || y == height || x == 0 || x == width)
    {
        DisplayGameOver();
    }
    switch (dir)
    {
    case None:
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }
}


int main() {
    srand(time(0));
    //w-119 a-97 s-115 d-100
    SpawnFruit();
    while (isPlaying)
    {
        DisplayBoard();
        Move();
        if (_kbhit())
        {
            switch (_getch())
            {
            case 119:
                dir = UP;
                break;
            case 97:
                dir = LEFT;
                break;
            case 115:
                dir = DOWN;
                break;
            case 100:
                dir = RIGHT;
                break;
            default:
                break;
            }
        }

    }
}