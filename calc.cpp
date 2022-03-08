#include <iostream>
#include <string.h>
using namespace std;
string dzialanie;
short znaki[20] = {0}; //przechowuje znaki aperacji matematycznej
short d = 0; //zmienna operacyjna dla pętli - |nadawanie piorytetu dla operacji matematycznej|
int bufor=0; //zmienna operacyjna dla pętli - |sortowanie piorytetu operacji matematycznej| - przechowuje numer tablicy 
int stos = -1;
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
    for (int x = 0; x < dzialanie.length(); x++) {
        for (int i = 0; i < dzialanie.length(); i++) {
            if (znaki[i] > znaki[bufor]) {
                bufor = i;
            }
        }
        cout << znaki[bufor] << ",";
        piorytet[x] = bufor;
        // cout << piorytet[x] << ",piorytet\n";
        znaki[bufor] = 0;
        bufor = 0;
    }
    cout << dzialanie[0] << dzialanie[1] << dzialanie[2] << dzialanie[3] << "\n";
    cout << piorytet[0] << piorytet[1] << piorytet[2] << piorytet[3] << "\n";
    int x = 0;
    for (int i = 0; i < dzialanie.length(); i++) {
        if (piorytet[i] > 0) {
            cout << piorytet[i] << ",piorytet\n";
            cout << dzialanie[piorytet[i]] << ",dzialanie\n";


//_________________________________________________
            //stos do naprawy


            switch (dzialanie[piorytet[i]])
            {
            case '+':
                if (stos > -1) {
                    stos = stos + (dzialanie[piorytet[i] + 1] - 48);
                }
                else {
                    stos = (dzialanie[piorytet[i] - 1]-48) + (dzialanie[piorytet[i] + 1]-48);
                    cout << dzialanie[piorytet[i] - 1] << " +" << dzialanie[piorytet[i] + 1]<<"=" << stos;
                }
                break;
            case '-':
                if (stos > -1) {
                    stos = stos - (dzialanie[piorytet[i] + 1]-48);
                }
                else {
                    stos = (dzialanie[piorytet[i] - 1]-48) - (dzialanie[piorytet[i]+1]-48);
                }
                break;
            case '*':
                if (stos > -1) {
                    stos = stos * (dzialanie[piorytet[i] + 1] - 48);
                }
                else {
                    stos = (dzialanie[piorytet[i] - 1] - 48) * (dzialanie[piorytet[i] + 1] - 48);
                }
                break;
            case '/':
                if (stos > -1) {
                    stos = stos / (dzialanie[piorytet[i] + 1] - 48);
                }
                else {
                    stos = (dzialanie[piorytet[i] - 1] - 48) / (dzialanie[piorytet[i] + 1] - 48);
                }
                break;
            }

            cout <<"stos" << stos <<"\n";
           
        }       
        
    }

    cout << "\n" << stos << ",";

}

