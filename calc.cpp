#include <iostream>
#include <string.h>
using namespace std;
//--------------stos-----------------------╗
bool czyPusty(double* sstos) {
    if (sstos[0] == 0)return true; else return false;
}
bool czyPelny(double* sstos) {
    if (sstos[0] == 100) return true; else return false;
}
void naStos(double x, double* sstos) {
    if (!czyPelny(sstos)) {
        sstos[0]++;
        sstos[(int)sstos[0]] = x;
    }
    else {
        cout << "stos pelny\n";
    }
}
double zeStosu(double* sstos) {
    if (!czyPusty(sstos)) {
        sstos[0]--;
        return sstos[(int)sstos[0] + 1];
    }
    else {
        cout << "stos jest pusty\n";
        return 0;
    }
}
double rozpalStos(double* sstos) {
    if (!czyPusty(sstos)) {
        return sstos[(int)sstos[0]];
    }
    else {
        cout << "stos jest pusty\n";
        return 0;
    }
}
//-----------------------------------------╝

// przekształca działanie na onp
string toOnp(string dzialanie) {

    int znaki[100] = { 0 }; //przechowuje znaki aperacji matematycznej
    short d = 0; //zmienna operacyjna dla pętli - |nadawanie piorytetu dla operacji matematycznej|
    short bufor = 0; //zmienna operacyjna dla pętli - |sortowanie piorytetu operacji matematycznej| - przechowuje numer tablicy 
    short piorytet[100] = { 0 }; //tablica piorytetu operacji matematycznej wskazuje na numer miejsce w tablicy
    string wynik = "";
    string poczekalnia = "";

    //nadawanie piorytetu dla operacji matematycznej
    for (short i = 0; i < dzialanie.length(); i++) {
        if (dzialanie[i] == '+' || dzialanie[i] == '-') znaki[i] = 1 + d;
        if (dzialanie[i] == '*' || dzialanie[i] == '/') znaki[i] = 2 + d;
        if (dzialanie[i] == '(') d += 10;
        if (dzialanie[i] == ')') d += -10;
    }

    //sortowanie piorytetu operacji matematycznej
    for (short x = 0; x < dzialanie.length(); x++) {
        for (short i = 0; i < dzialanie.length(); i++) {
            if (znaki[i] > znaki[bufor]) {
                bufor = i;
            }
        }
        piorytet[x] = bufor;
        znaki[bufor] = 0;
        bufor = 0;
    }

    //zapisz w onp
    for (short i = 0; i < dzialanie.length(); i++) {
        if (piorytet[i] > 0) {
            if (dzialanie[piorytet[i] + 1] == '(' && dzialanie[piorytet[i] - 1] != ')' && dzialanie[piorytet[i] - 1] != '(' && dzialanie[piorytet[i] - 1] != '!') {

                poczekalnia += dzialanie[piorytet[i] - 1];
                dzialanie[piorytet[i] - 1] = '!'; //oznacz liczbę jako wykorzystaną
            }
            if (dzialanie[piorytet[i] - 1] != ')' && dzialanie[piorytet[i] - 1] != '(' && dzialanie[piorytet[i] - 1] != '!')
            {
                wynik += dzialanie[piorytet[i] - 1];
                dzialanie[piorytet[i] - 1] = '!'; //oznacz liczbę jako wykorzystaną 
            }
            if (dzialanie[piorytet[i] + 1] != '(' && dzialanie[piorytet[i] + 1] != ')' && dzialanie[piorytet[i] + 1] != '!')
            {
                wynik += dzialanie[piorytet[i] + 1];
                dzialanie[piorytet[i] + 1] = '!'; //oznacz liczbę jako wykorzystaną
            }
            wynik = poczekalnia + wynik + dzialanie[piorytet[i]];
            poczekalnia = "";
        }
    }
    return wynik;
}

 //wykonuje obliczenia wykorzystujac ONP
double licz(string onpString, double* sstos) {
    for (short i = 0; i < onpString.length(); i++) {

        if (onpString[i] != '-' && onpString[i] != '+' && onpString[i] != '/' && onpString[i] != '*') {
            onpString[i] -= 48;
            naStos(onpString[i], sstos);
        }
        else {
            double b = zeStosu(sstos);
            double a = zeStosu(sstos);
            switch (onpString[i]) {
            case  '+':
                naStos(a + b, sstos);

                break;
            case '-':
                naStos(a - b, sstos);

                break;
            case '*':
                naStos(a * b, sstos);

                break;
            case '/':
                naStos(a / b, sstos);
                break;
            }
        }
    }
    return rozpalStos(sstos);
}

int main()
{
    // przechowuje działanie matematyczne
    string dzialanie;
    dzialanie = "((1+1)+3)-(9+1-2)";

    //cin >> dzialanie;
    //cout << endl << dzialanie << endl;

    //wyświetl i zapisz działanie jako ONP
    cout << endl << "zapis onp : " << toOnp(dzialanie) << endl;

    double stos1[100] = { 0 }; //tworzenie nowego stosu
    stos1[0] = 0; //pływak stosu

    //wyświetl wynik
    cout << endl << "wynik: " << licz(toOnp(dzialanie), stos1) << endl;
}