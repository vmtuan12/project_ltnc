#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int wrongAns = 0, correctAns = 0;

void firstDisplay(string word);
void play(string s1);
void check(string s, char c);
void reDraw(int x);
string guessAns(string s);
string convertToString(char* a, int size);

int main()
{
    string word;
    cout << "Enter the word for the others to guess: ";
    while(true){
        getline(cin,word);
        bool notLetter = false;
        for(int i = 0; i < word.length(); i++){
            if(!('a' <= word[i] && word[i] <= 'z') && !('A' <= word[i] && word[i] <= 'Z')){
                notLetter = true;
                break;
            }
        }
        if(notLetter == false) break;
        else cout << "Invalid character" << endl
                  << "Please re-enter the word: ";
    }

    firstDisplay(word);
    play(word);
    return 0;
}

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void firstDisplay(string word)
{
    cout << "Game start" << endl
         << "  --------" << endl 
         << "  |" << endl << "  |" << endl <<  "  |" << endl << "  |" << endl
         << "-----" << endl
         << "Secret word: ";
    for(int i = 0; i < word.length(); i++){
        cout << "-";
    }
    cout << endl << "Length of the word: " << word.length() << endl;
}

void reDraw(int x)
{
    cout << "  -----------" << endl;
    for(int i = 1; i <= 4; i++){
        cout << "  |";
        if(i == 1)
            if(x >= 1) cout << "      |";
        
        if(i == 2)
            if(x >= 2) cout << "      o";
        
        if(i == 3){
            if(x == 3) cout << "      |";
            if(x >= 4) cout << "     /|";
            if(x >= 5) cout << (char)92;
        }
        if(i == 4){
            if(x >= 6) cout << "     / ";
            if(x == 7) cout << (char)92;
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

void play(string s1)
{
    int len = s1.length();
    string hiddenAns = "";
    for(int i = 0; i < len; i++){
        hiddenAns += "-";
    }
    while(true){
        string ans;
        ans = guessAns(s1);
        if(ans != "-1"){
            if(ans == s1){
                cout << "You win" << endl
                    << "The answer is: " << s1 << endl;
                break;
            }
            else{
                cout << "You lose" << endl
                     << "The answer is: " << s1 << endl;
                break;
            }
        }

        char guess;
        cout << "Guess a letter: ";
        while(true){
            cin >> guess;
            if(!('a' <= guess && guess <= 'z') && !('A' <= guess && guess <= 'Z'))
                cout << "Invalid character" << endl
                     << "The letter must be between 'a' and 'z'" << endl
                     << "Please re-enter the letter: ";
            else break;
        }

        bool repeat = false;
        for(int i = 0; i < s1.length(); i++){
            if(guess == hiddenAns[i]){
                repeat = true;
                break;
            }
        }
        if(repeat) {
            cout << "You can't choose the letter which has already been revealed" << endl
                 << "Please pick another letter" << endl;
            continue;
        }

        int match = 0;
        for(int i = 0; i < s1.length(); i++){
            if(guess == s1[i]) match++;
        }
        
        if(match == 1){
            correctAns++;
            if(correctAns == s1.length()){
                cout << "You win" << endl
                     << "The answer is: " << s1 << endl;
                break;
            }
            cout << "There is 1 '" << guess << "'" << endl;
            for(int i = 0; i < s1.length(); i++){
                if(s1[i] == guess) hiddenAns[i] = guess;
            }
            cout << hiddenAns << endl;
        }

        if(match > 1){
            correctAns += match;
            if(correctAns == s1.length()){
                cout << "You win" << endl
                     << "The answer is: " << s1 << endl;
                break;
            }
            cout << "There are " << match << " '" << guess << "'" << endl;
            for(int i = 0; i < s1.length(); i++){
                if(s1[i] == guess) hiddenAns[i] = guess;
            }
            cout << hiddenAns << endl;
        }
    
        if(match == 0){
            wrongAns++;
            cout << "There is no '" << guess << "'" << endl;
            reDraw(wrongAns);
            if(wrongAns == 7){
                cout << "You lose" << endl
                     << "The answer is: " << s1 << endl;
                break;
            }
            cout << "Secret word: " << hiddenAns << endl;
        }
        
    }
}

string guessAns(string s)
{
    string ans;
    cout << "Press '1' if you want to get straight to the answer" << endl
         << "      '2' to guess a single letter" << endl
         << "*If you guess the answer wrong, you will lose immidiately, be careful!" << endl;
    char x;
    while(true){
        cin >> x;
        cin.ignore();
        if(!('1' <= x && x <= '2')){
            cout << "Invalid input" << endl;
            continue;
        }
        if(x == '1'){
            string a;
            cout << "Your answer is: ";
            getline(cin,a);
            ans = a;
            break;
        }
        if(x == '2'){
            ans = "-1";
            break;
        }
    }
    return ans;

}

