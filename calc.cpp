#include <iostream>
#include <string.h>
using namespace std;
//--------------stos-----------------------╗
bool czyPusty(int* sstos) {
    if (sstos[0] == 0)return true; else return false;
}
bool czyPelny(int* sstos) {
    if (sstos[0] == 10) return true; else return false;
}
void naStos(int x, int* sstos) {
    if (!czyPelny(sstos)) {
        sstos[0]++;
        sstos[sstos[0]] = x;
        cout <<"dodano: " << x << " na stos"<<endl;
    }
    else {
        cout << "stos pelny\n";
    }
}
int zeStosu(int* sstos) {
    if (!czyPusty(sstos)) {
        sstos[0]--;
        return sstos[sstos[0] + 1];
    }
    else {
        cout << "stos jest pusty\n";
        return -999;
    }
}
int rozpalStos(int* sstos) {
    if (!czyPusty(sstos)) {
        cout << sstos[sstos[0]]<<endl;
        return sstos[sstos[0]];
    }
    else {
        cout << "stos jest pusty\n";
        return -999;
    }
}
//-----------------------------------------╝
int licz(int* ssstos, char b) {
    cout<< "b:" << b<<endl;
    switch (b) {
    case  '+':
        //cout << "dodawanie";
        return zeStosu(ssstos) + zeStosu(ssstos);
        break;
    case '-':
        //cout << "odejmowanie";
        return zeStosu(ssstos) - zeStosu(ssstos);
        break;
    case '*':
        //cout << "mnozenie";

        return zeStosu(ssstos) * zeStosu(ssstos);
        break;
    case '/':
        //cout << "dzielenie";
        return zeStosu(ssstos) / zeStosu(ssstos);
        break;
    default:
        cout << "errroo";
        return 0;
    }

}

int main()
{
    string dzialanie = "1+(2*(3+4))";
    int znaki[20] = { 0 }; //przechowuje znaki aperacji matematycznej
    short d = 0; //zmienna operacyjna dla pętli - |nadawanie piorytetu dla operacji matematycznej|
    short bufor = 0; //zmienna operacyjna dla pętli - |sortowanie piorytetu operacji matematycznej| - przechowuje numer tablicy 
    short piorytet[20] = { 0 }; //tablica piorytetu operacji matematycznej

    //cin >> dzialanie;
    //nadawanie piorytetu dla operacji matematycznej
    for (int i = 0; i < dzialanie.length(); i++) {
        if (dzialanie[i] == '+' || dzialanie[i] == '-') znaki[i] = 1 + d;
        if (dzialanie[i] == '*' || dzialanie[i] == '/') znaki[i] = 2 + d;
        if (dzialanie[i] == '(') d += 10;
        if (dzialanie[i] == ')') d += -10;
        //cout << znaki[i] << ",";
    }
    //cout << "tab\n";
    //sortowanie piorytetu operacji matematycznej
    for (int x = 0; x < dzialanie.length(); x++) {
        for (int i = 0; i < dzialanie.length(); i++) {
            if (znaki[i] > znaki[bufor]) {
                bufor = i;
            }
        }
        //cout << znaki[bufor] << ",";
        piorytet[x] = bufor;
        znaki[bufor] = 0;
        bufor = 0;
    }
    for (int i = 0; i < dzialanie.length(); i++) {
        if (piorytet[i] > 0) {
            //cout << endl << piorytet[i] << ",piorytet\n";
            //cout << dzialanie[piorytet[i]] << ",dzialanie\n";
        }

    }
    int stos1[11] = { 0 };
    stos1[0] = 0; //pływak stosu

    naStos(dzialanie[piorytet[0] - 1]- 48, stos1);
    naStos(dzialanie[piorytet[0] + 1] - 48, stos1);
    naStos(licz(stos1, dzialanie[piorytet[0]]),stos1);

    for (int i = 1; i < dzialanie.length() && piorytet[i] > 0; i++) {
            naStos(dzialanie[piorytet[i] - 1] - 48, stos1);
            naStos(licz(stos1, dzialanie[piorytet[i]]), stos1);
            
    }
    rozpalStos(stos1);

}