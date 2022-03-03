#include <iostream>
#include <string.h>
using namespace std;
string dzialanie;
short znaki[20] = {0}; //przechowuje działanie podzielone na pojedyńcze znaki
short d = 0; //zmienna operacyjna dla pędtli - |nadawanie piorytetu dla operacji matematycznej|
int bufor=0; //zmienna operacyjna dla pędtli - |sortowanie piorytetu operacji matematycznej|
short piorytet[20] = {0}; //tablica piorytetu operacji matematycznej
int main()
{
    cin >> dzialanie;
    //nadawanie piorytetu dla operacji matematycznej
    for (int i = 0; i < dzialanie.length(); i++) {
        if (dzialanie[i] == '+' || dzialanie[i] == '-') znaki[i] = 1 + d;
        if (dzialanie[i] == '*' || dzialanie[i] == '/') znaki[i] = 2 + d;
        if (dzialanie[i] == '(') d += 10;
        if (dzialanie[i] == ')') d += -10;
        cout << znaki[i] << ",";
    }
    cout << "tab\n";
    //sortowanie piorytetu operacji matematycznej
    for (int x = 0; x < dzialanie.length(); x++){
        for (int i = 0; i < dzialanie.length(); i++) {
            if (znaki[i] > bufor) {
                bufor = i;
            }
        }
        cout << znaki[bufor] << ",";
        piorytet[x] = znaki[bufor];
        znaki[bufor] = 0;
        bufor = 0;
    }

  /*  for (int i = 0; i < dzialanie.length(); i++) {
        stos[i]
    }*/

}

