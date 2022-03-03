#include <iostream>
#include <time.h>
#include <sstream>
#include <cstdlib>
using namespace std;

void play()
{
    int n;
    int r = 1 + rand()%100;
    while(n != r){
        cin >> n;
        if(n == r) cout << "You win" << endl;
        if(n < r) cout << "Too small" << endl;
        if(n > r) cout << "Too big" << endl;
    }

}

int main()
{
    srand((int)time(0));
    while(true){
        cout << "Press 'q' to quit" << endl << "      any other key to play" << endl;
        string button;
        cin >> button;

        if(button == "q"){
            cout << "Game over" << endl;
            break;
        }
        else play();
    }
}