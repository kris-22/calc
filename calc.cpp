#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    string dzialanie;  //przechowuje działania matematyczne
    double stos1[100] = { 0 }; //tworzenie nowego stosu
    stos1[0] = 0; //pływak stosu
    short select;

    cout << "|--------------wybierz--------------|"<<endl;
    cout << "1. Program liczacu ONP" << endl;
    cout << "2. Informacje o programie" << endl;
    cout << "3. wyjscie" << endl;
    cout << "|-----------------------------------|"<<endl;
    cout << ": ";
    cin >> select;

    //menu wyboru
    switch (select)
    {
    case 1:
        system("cls");
        cout << "podaj dzialanie: ";
        cin >> dzialanie;

        //wyświetl i zapisz działanie jako ONP
        cout << endl << "zapis onp : " << toOnp(dzialanie) << endl;

        //wyświetl wynik
        cout << endl << "wynik: " << licz(toOnp(dzialanie), stos1) << endl;
        break;
    case 2:
        system("cls");
        cout << "Autor : Krzysztof Bielecki" << endl << "Versja : 2.1" << endl;
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }


  
}