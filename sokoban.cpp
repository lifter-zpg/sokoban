// sokoban.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;

void ekran_powitalny()
{
    /*cout << "ooooooo_ooo____oo___________________________ooo_____ooo__oo_________________________oo__________oo___oooooo____ooooo____oo____oo___oooooo__" << endl;
    cout << "oo_______oo_________ooooo___oooo__oooooo____oooo___oooo_______ooooo__oooooo__ooooo__oo___o____oooo__oo____oo_oo____oo_oooo__oooo__oo_______" << endl;
    cout << "oooo_____oo____oo__oo___oo_oo___o______o____oo_oo_oo_oo__oo__oo___oo______o_oo____o_oo__o_______oo__oo____oo_______oo___oo____oo__ooooooo__"<< endl;
    cout << "oo_______oo____oo__oo___oo___oo______oo_____oo__ooo__oo__oo__oo___oo____oo__ooooooo_oooo________oo___ooooooo_____ooo____oo____oo__oo____oo_" << endl;
    cout << "oo_______oo____oo__oo___oo_o___oo__oo_______oo_______oo__oo__oo___oo__oo____oo______oo__o_______oo__o_____oo_oo____oo___oo____oo__oo____oo_" << endl;
    cout << "ooooooo_ooooo_oooo__oooo_o__oooo__oooooo____oo_______oo_oooo__oooo_o_oooooo__ooooo__oo___o____ooooo__oooooo___oooooo__ooooo_ooooo__oooooo__"<<endl;*/
   

    cout << "___              __  __                 __  ___                 ,   _,  _,  ,   ,  ._ " << endl;
    cout << "|__  |    |  /\\  /__`  /     |\\/| |  /\\   / |__  |__/          /|  (_) '_) /|  /|  (_ " << endl;
    cout << "|___ |___ | /~~\\ .__/ /_     |  | | /~~\\ /_ |___ |  \\          .|.   | ._) .|. .|. (_)" << endl;
    cout << " ___  __       __   __   __       " << endl;
    cout << "[__  |  | |_/ |  | |__] /__\\ |\\ | " << endl;
    cout << "___] |__| | \\ |__| |__] |  | | \\| " << endl;
}

int main()
{
    ekran_powitalny();
    Sleep(3000);
    system("cls");
    cout << "WASD - poruszanie sie  Q - menu glowne  U - undo R - redo  J,K,I,M - przesuwanie pola" << endl;
    //tworzenie mapek
  //  char mapa[1][10][10];
    char mapa[2][10][10] = 
    {
        {
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'},
            { '0','0','0','0','0','0','0','0','0','0'}
        },

        {
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'},
            { '1','1','1','1','1','1','1','1','1','1'}
        }
    };

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 10; ++j) 
        {
            for (int k = 0; k < 10; ++k)
            {
                cout << mapa[i][j][k]<<" ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln

