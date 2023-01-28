#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;


bool isPlaying = true;
int width = 32;
int height = 12;
int x = 16;
int y = 6;


void cls()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}

void DisplayBoard(){
    sleep(0.3);
    cls();
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (j == 0 || j == width || i == 0 || i == height)
            {
                cout << "#";
                continue;
            }
            if(i == y && j == x){
                cout << "O";
                continue;
            }
            cout << " ";                
        }
        cout << endl;
    }    

}


int main(){
    while (isPlaying)
    {
        DisplayBoard();
    }
}