// calc.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string.h>
using namespace std;
string dzialanie;
short znaki[20] = { 0 };
short d = 0;
int bufor=0;
short stos[20] = {0}; //tablica piorytetu operacji matematycznej
int main()
{
    cin >> dzialanie;
    //nadawanie piorytetu dla działań
    for (int i = 0; i < dzialanie.length(); i++) {
        if (dzialanie[i] == '+' || dzialanie[i] == '-') znaki[i] = 1 + d;
        if (dzialanie[i] == '*' || dzialanie[i] == '/') znaki[i] = 2 + d;
        if (dzialanie[i] == '(') d += 10;
        if (dzialanie[i] == ')') d += -10;
        cout << znaki[i] << ",";
    }
    cout << "tab\n";

    for (int x = 0; x < dzialanie.length(); x++){
        for (int i = 0; i < dzialanie.length(); i++) {
            if (znaki[i] > bufor) {
                bufor = i;
            }
        }
        cout << znaki[bufor] << ",";
        stos[x] = znaki[bufor];
        znaki[bufor] = 0;
        bufor = 0;
    }

  /*  for (int i = 0; i < dzialanie.length(); i++) {
        stos[i]
    }*/

}

