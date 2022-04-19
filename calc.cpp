#include <iostream>
#include <string.h>
using namespace std;
//--------------stos-----------------------╗
bool czyPusty(double *sstos) {
    if (sstos[0] == 0)return true; else return false;
}
bool czyPelny(double* sstos) {
    if (sstos[0] == 20) return true; else return false;
}
void naStos(double x, double* sstos) {
    if (!czyPelny(sstos)) {
        sstos[0]++;
        sstos[(int)sstos[0]] = x;
        //cout <<"dodano: " << x << " na stos"<<endl;
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
        //cout <<"rozpalono" << sstos[(int)sstos[0]] << endl;
        return sstos[(int)sstos[0]];
    }
    else {
        cout << "stos jest pusty\n";
        return 0;
    }
}
//-----------------------------------------╝
string toOnp(string dzialanie) {

    int znaki[20] = { 0 }; //przechowuje znaki aperacji matematycznej
    short d = 0; //zmienna operacyjna dla pętli - |nadawanie piorytetu dla operacji matematycznej|
    short bufor = 0; //zmienna operacyjna dla pętli - |sortowanie piorytetu operacji matematycznej| - przechowuje numer tablicy 
    short piorytet[20] = { 0 }; //tablica piorytetu operacji matematycznej
    string wynik = "";

    //nadawanie piorytetu dla operacji matematycznej
    for (int i = 0; i < dzialanie.length(); i++) {
        if (dzialanie[i] == '+' || dzialanie[i] == '-') znaki[i] = 1 + d;
        if (dzialanie[i] == '*' || dzialanie[i] == '/') znaki[i] = 2 + d;
        if (dzialanie[i] == '(') d += 10;
        if (dzialanie[i] == ')') d += -10;
        //cout << znaki[i] << ",";
    }
    cout << endl;

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

    //zapisz w onp
    for (int i = 0; i < dzialanie.length(); i++) {
        if (piorytet[i] > 0) {
            if (dzialanie[piorytet[i] - 1] != ')' && dzialanie[piorytet[i] - 1] != '(' && dzialanie[piorytet[i] - 1] != '!')
            {
                wynik += dzialanie[piorytet[i] - 1];
                dzialanie[piorytet[i] - 1] = '!'; //onacz liczbę jako wykorzystaną 
            }
            if (dzialanie[piorytet[i] + 1] != '(' && dzialanie[piorytet[i] + 1] != ')' && dzialanie[piorytet[i] + 1] != '!')
            {
                wynik += dzialanie[piorytet[i] + 1];
                dzialanie[piorytet[i] + 1] = '!'; //onacz liczbę jako wykorzystaną
            }
            wynik += dzialanie[piorytet[i]];
        }
    }
    return wynik;

}

double licz(string onpString , double* sstos ) {
    for (int i = 0; i < onpString.length(); i++) {
        //cout << "eee" << endl;

        if (onpString[i] != '-' && onpString[i] != '+' && onpString[i] != '/' && onpString[i] != '*') {
            onpString[i] -= 48;
            naStos(onpString[i], sstos);
        }
        else {
            cout << "Licze" <<endl;
            double a = zeStosu(sstos);
            double b = zeStosu(sstos);
            switch (onpString[i]) {
            case  '+':
                cout << onpString[i] << endl;
                naStos(a + b, sstos);
                cout << rozpalStos(sstos) << endl;

                break;
            case '-':
                cout << onpString[i] << endl;
                naStos(b - a, sstos);
                cout << rozpalStos(sstos) << endl;

                break;
            case '*':
                //cout << onpString[i] << endl;
                naStos(a * b, sstos);
                //cout << rozpalStos(sstos) << endl;

                break;
            case '/':
                //cout << onpString[i] << endl;
                naStos(b / a, sstos);
                //cout << rozpalStos(sstos) << endl;
                break;
            }
        }
    }
    return rozpalStos(sstos);
}


int main()
{
    //string dzialanie = "2-2+3+(2+2)-2";
    //string dzialanie = "(2+3)*(3*(4+6))";
    string dzialanie = "8-(2+3)";
    //string dzialanie = "2+2*(3/(2+4)/2)";

    //cin >> dzialanie; 
    cout <<endl<< dzialanie<<endl;
    cout << endl <<"zapis onp : " << toOnp(dzialanie) << endl;



    double stos1[11] = { 0 }; //tworzenie nowego stosu
    stos1[0] = 0; //pływak stosu
    cout <<endl<<"wynik: " << licz(toOnp(dzialanie), stos1);
}



//dzialanie[piorytet[i] - 1 = ")"
