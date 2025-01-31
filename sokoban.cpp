#include <iostream>
#include <iomanip>

//mapa przekazana - mapa "czysta" ktorej nie bede modyfikowal
//mapa === mapy - mapa, ktora sobie modyfikuje
#define mapaY 10
#define mapaZ 10
using namespace std;

//int odblokowany_lvl = 0;
int maks(int* x, int y);
int menu(int* odblokowany_lvl);
void zaladujMape(char mapa[4][mapaY][mapaZ], char mapa_przekazana[4][mapaY][mapaZ], int jakamapa);
bool czy_ruch(char poruszenie, int nr_mapy, int gracz_x, int gracz_y, char mapy[4][mapaY][mapaZ]);
void rozgrywka(char mapy[4][mapaY][mapaZ], int nr_mapy, char mapa_przekazana[4][mapaY][mapaZ], int* odblokowany_lvl);
bool wygrana(char mapy[4][mapaY][mapaZ], int nr_mapy, int* odblokowany_lvl); // 1 - wygrana, 0 - brak wygranej
int maks(int* x, int y)
{
    if (*x >= y)
        return *x;
    else
        return y;
}
void zaladujMape(char mapa[4][mapaY][mapaZ], char mapa_przekazana[4][mapaY][mapaZ], int jakamapa)
{
    for (int k = 0; k < 4; ++k)
    {
        for (int i = 0; i < mapaY; ++i)
        {
            for (int j = 0; j < mapaZ; ++j)
                mapa_przekazana[k][i][j] = mapa[k][i][j];
        }
    }
}
bool czy_ruch(char poruszenie, int nr_mapy, int gracz_x, int gracz_y, char mapy[4][mapaY][mapaZ])
{
    //jesli ruch jest poprawny - 1, jesli nie  - 0
    if (
        ((poruszenie == 'W' or poruszenie == 'w') and ((mapy[nr_mapy][gracz_y - 1][gracz_x] != '#') and mapy[nr_mapy][gracz_y - 1][gracz_x] != 'D')) or
        ((poruszenie == 'A' or poruszenie == 'a') and ((mapy[nr_mapy][gracz_y][gracz_x - 1] != '#') and mapy[nr_mapy][gracz_y][gracz_x - 1] != 'D')) or
        ((poruszenie == 'S' or poruszenie == 's') and ((mapy[nr_mapy][gracz_y + 1][gracz_x] != '#') and mapy[nr_mapy][gracz_y + 1][gracz_x] != 'D')) or
        ((poruszenie == 'D' or poruszenie == 'd') and ((mapy[nr_mapy][gracz_y][gracz_x + 1] != '#') and mapy[nr_mapy][gracz_y][gracz_x + 1] != 'D'))
        )
        return 1;

    return 0;
}


void ekran_powitalny()
{
    cout << "___              __  __                 __  ___                 ,   _,  _,  ,   ,  ._ " << endl;
    cout << "|__  |    |  /\\  /__`  /     |\\/| |  /\\   / |__  |__/          /|  (_) '_) /|  /|  (_ " << endl;
    cout << "|___ |___ | /~~\\ .__/ /_     |  | | /~~\\ /_ |___ |  \\          .|.   | ._) .|. .|. (_)" << endl;
    cout << " ___  __       __   __   __       " << endl;
    cout << "[__  |  | |_/ |  | |__] /__\\ |\\ | " << endl;
    cout << "___] |__| | \\ |__| |__] |  | | \\| " << endl;
    char decyzja;
    cout << "Podaj 1 na wyjscie, aby wylaczyc ekran powitalny" << endl;
    do
    {
        cin >> decyzja;
        if (decyzja == '1')
            system("cls");
        else
            cout << "Podaj poprawny znak" << endl;

    } while (decyzja != '1');
}
int menu(int* odblokowany_lvl)
{
    // poczatek estetyki
    char blok = char(254);
    for (int i = 0; i < 28; i++)
    {
        cout << blok;
    }
    cout << endl;
    cout << blok << "Witamy w menu gry Sokoban." << blok << endl;
    for (int i = 0; i < 28; i++)
    {
        cout << blok;
    }
    cout << "\n @ - gracz \n & - gracz, ktory stoi na polu, na skrzynie \n S - skrzynia \n X - miejsce, w ktore nalezy przepchac skrzynie \n D - odlozona skrzynia\n";
    cout << "\n\nPodaj numer poziomu, ktory chcesz rozegrac (1-4)\nPodaj 5, aby wyjsc z gry\n";
    // koniec estetyki
    char decyzja;
    do {
        cin >> decyzja;
        if (decyzja < '1' or decyzja>'5')
        {
            cout << "Podaj poprawna decyzje (1-5)" << endl;
        }

        if (*odblokowany_lvl < (decyzja - 49) and (decyzja >= '1' and decyzja < '5'))
        {
            cout << "Nie mozesz zagrac tego poziomu" << endl;
        }
        else if (decyzja == '5')
        {
            cout << "Dziekuje za rozgrywke, Eliasz Miazek" << endl;
            exit(0);
        }

    } while (decyzja < '1' or decyzja > '5' or *odblokowany_lvl < (decyzja - 49));

    system("cls");

    int nr_mapy = decyzja - 49; //-49, bo tak naprawde gdy podaje na wejscie charowa jedynke, to chce zajrzec w zerowy element tablicy

    return nr_mapy;
}

void rozgrywka(char mapy[4][mapaY][mapaZ], int nr_mapy, char mapa_przekazana[4][mapaY][mapaZ], int* odblokowany_lvl)
{
    char mapa_przekazywana[4][mapaY][mapaZ];
    zaladujMape(mapy, mapa_przekazywana, nr_mapy);//ladowanie czystej, nietknietej mapy

    cout << "Witamy w rozgrywce\n";
    char ruch;
    int gracz_x = 5, gracz_y = 5;

    for (int j = 0; j < 10; ++j)
    {
        for (int k = 0; k < 10; ++k)
        {
            cout << mapy[nr_mapy][j][k] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int dostepne_ruchy = int(mapy[nr_mapy][0][0]); //ilosc ruchow mam schowane w indeksie [0][0]

    while (cin)
    {
        cout << "Pula dostepnych ruchow: " << dostepne_ruchy << endl;
        cout << "Masz dosc lub wiesz, ze przegrasz i chcesz ponownie sprobowac swoich sil?" << endl;
        cout << "Wcisnij Q i zatwierdz enterem, aby powrocic do menu" << endl;

        cin >> ruch;
        system("cls");
        if (czy_ruch(ruch, nr_mapy, gracz_x, gracz_y, mapy))
            dostepne_ruchy -= 1;

        if (dostepne_ruchy >= 0)
        {
            switch (ruch)
            {
            case 'W':
            case 'w':
                if (mapy[nr_mapy][gracz_y][gracz_x] == '&' and mapy[nr_mapy][gracz_y - 1][gracz_x] != '#')
                {
                    mapy[nr_mapy][gracz_y - 1][gracz_x] = '@';
                    mapy[nr_mapy][gracz_y][gracz_x] = 'X';
                    gracz_y--;
                }
                else
                {
                    if (mapy[nr_mapy][gracz_y - 1][gracz_x] != '#')
                    {
                        if (mapy[nr_mapy][gracz_y - 1][gracz_x] == '_')
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y - 1][gracz_x] = '@';
                            gracz_y--;
                        }
                        else if (mapy[nr_mapy][gracz_y - 1][gracz_x] == 'S')
                        {
                            if (mapy[nr_mapy][gracz_y - 2][gracz_x] == '_')
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';
                                mapy[nr_mapy][gracz_y - 1][gracz_x] = '@';
                                mapy[nr_mapy][gracz_y - 2][gracz_x] = 'S';
                                gracz_y--;
                            }
                            else if (mapy[nr_mapy][gracz_y - 2][gracz_x] == 'X') // X - miejsce na skrzynke
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';     // _ puste pole
                                mapy[nr_mapy][gracz_y - 1][gracz_x] = '@'; // @ - gracz
                                mapy[nr_mapy][gracz_y - 2][gracz_x] = 'D'; // D - skrzynka odlozona
                                gracz_y--;
                            }
                            else
                                cout << "Nie moge tam wejsc" << endl;
                        }
                        else if (mapy[nr_mapy][gracz_y - 1][gracz_x] == 'X') //jesli gracz wejdzie na X, staje sie ampersandem
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y - 1][gracz_x] = '&';
                            cout << "Stoisz na polu, na ktorym ma znalezc sie skrzynia!" << endl;
                            cout << "Twoj piktogram zmienil sie w '&'" << endl;
                            gracz_y--;
                        }
                        cout << "Wprowadziles w" << endl;
                    }
                    else
                        cout << "Nie moge wejsc w sciane!" << endl;
                }
                break;
            case 'A':
            case 'a':
                if (mapy[nr_mapy][gracz_y][gracz_x] == '&' and mapy[nr_mapy][gracz_y][gracz_x - 1] != '#')
                {
                    mapy[nr_mapy][gracz_y][gracz_x - 1] = '@';
                    mapy[nr_mapy][gracz_y][gracz_x] = 'X';
                    gracz_x--;
                }
                else
                {
                    if (mapy[nr_mapy][gracz_y][gracz_x - 1] != '#')
                    {
                        if (mapy[nr_mapy][gracz_y][gracz_x - 1] == '_')
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y][gracz_x - 1] = '@';
                            gracz_x--;
                        }
                        else if (mapy[nr_mapy][gracz_y][gracz_x - 1] == 'S')
                        {
                            if (mapy[nr_mapy][gracz_y][gracz_x - 2] == '_')
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';
                                mapy[nr_mapy][gracz_y][gracz_x - 1] = '@';
                                mapy[nr_mapy][gracz_y][gracz_x - 2] = 'S';
                                gracz_x--;
                            }
                            else if (mapy[nr_mapy][gracz_y][gracz_x - 2] == 'X') // X - miejsce na skrzynke
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';     // _ puste pole
                                mapy[nr_mapy][gracz_y][gracz_x - 1] = '@'; // @ - gracz
                                mapy[nr_mapy][gracz_y][gracz_x - 2] = 'D'; // D - skrzynka odlozona
                                gracz_x--;
                            }
                            else
                                cout << "Nie moge tam wejsc" << endl;
                        }
                        else if (mapy[nr_mapy][gracz_y][gracz_x - 1] == 'X') //jesli gracz wejdzie na X, staje sie ampersandem
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y][gracz_x - 1] = '&';
                            gracz_x--;
                            cout << "Stoisz na polu, na ktorym ma znalezc sie skrzynia!" << endl;
                            cout << "Twoj piktogram zmienil sie w '&'" << endl;
                        }
                        cout << "Wprowadziles a" << endl;
                    }
                    else
                        cout << "Nie moge wejsc w sciane!" << endl;
                }
                break;
            case 'S':
            case 's':
                if (mapy[nr_mapy][gracz_y][gracz_x] == '&' and mapy[nr_mapy][gracz_y + 1][gracz_x] != '#')
                {
                    mapy[nr_mapy][gracz_y + 1][gracz_x] = '@';
                    mapy[nr_mapy][gracz_y][gracz_x] = 'X';
                    gracz_y++;
                }
                else
                {
                    if (mapy[nr_mapy][gracz_y + 1][gracz_x] != '#')
                    {
                        if (mapy[nr_mapy][gracz_y + 1][gracz_x] == '_')
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y + 1][gracz_x] = '@';
                            gracz_y++;
                        }
                        else if (mapy[nr_mapy][gracz_y + 1][gracz_x] == 'S')
                        {
                            if (mapy[nr_mapy][gracz_y + 2][gracz_x] == '_')
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';
                                mapy[nr_mapy][gracz_y + 1][gracz_x] = '@';
                                mapy[nr_mapy][gracz_y + 2][gracz_x] = 'S';
                                gracz_y++;
                            }
                            else if (mapy[nr_mapy][gracz_y + 2][gracz_x] == 'X') // X - miejsce na skrzynke
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';     // _ puste pole
                                mapy[nr_mapy][gracz_y + 1][gracz_x] = '@'; // @ - gracz
                                mapy[nr_mapy][gracz_y + 2][gracz_x] = 'D'; // D - skrzynka odlozona
                                gracz_y++;
                            }
                            else
                                cout << "Nie moge tam wejsc" << endl;
                        }
                        else if (mapy[nr_mapy][gracz_y + 1][gracz_x] == 'X') //jesli gracz wejdzie na X, staje sie ampersandem
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y + 1][gracz_x] = '&';
                            gracz_y++;
                            cout << "Stoisz na polu, na ktorym ma znalezc sie skrzynia!" << endl;
                            cout << "Twoj piktogram zmienil sie w '&'" << endl;
                        }

                        cout << "Wprowadziles s" << endl;
                    }
                    else
                        cout << "Nie moge wejsc w sciane!" << endl;
                }
                break;
            case 'D':
            case 'd':
                if (mapy[nr_mapy][gracz_y][gracz_x] == '&' and mapy[nr_mapy][gracz_y][gracz_x + 1] != '#')
                {
                    mapy[nr_mapy][gracz_y][gracz_x + 1] = '@';
                    mapy[nr_mapy][gracz_y][gracz_x] = 'X';
                    gracz_x++;
                }
                else
                {
                    if (mapy[nr_mapy][gracz_y][gracz_x + 1] != '#')
                    {
                        if (mapy[nr_mapy][gracz_y][gracz_x + 1] == '_')
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y][gracz_x + 1] = '@';
                            gracz_x++;
                        }
                        else if (mapy[nr_mapy][gracz_y][gracz_x + 1] == 'S')
                        {
                            if (mapy[nr_mapy][gracz_y][gracz_x + 2] == '_')
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';
                                mapy[nr_mapy][gracz_y][gracz_x + 1] = '@';
                                mapy[nr_mapy][gracz_y][gracz_x + 2] = 'S';
                                gracz_x++;
                            }
                            else if (mapy[nr_mapy][gracz_y][gracz_x + 2] == 'X') // X - miejsce na skrzynke
                            {
                                mapy[nr_mapy][gracz_y][gracz_x] = '_';     // _ puste pole
                                mapy[nr_mapy][gracz_y][gracz_x + 1] = '@'; // @ - gracz
                                mapy[nr_mapy][gracz_y][gracz_x + 2] = 'D'; // D - skrzynka odlozona
                                gracz_x++;
                            }
                            else
                                cout << "Nie moge tam wejsc" << endl;
                        }
                        else if (mapy[nr_mapy][gracz_y][gracz_x + 1] == 'X') //jesli gracz wejdzie na X, staje sie ampersandem
                        {
                            mapy[nr_mapy][gracz_y][gracz_x] = '_';
                            mapy[nr_mapy][gracz_y][gracz_x + 1] = '&';
                            gracz_x++;
                            cout << "Stoisz na polu, na ktorym ma znalezc sie skrzynia!" << endl;
                            cout << "Twoj piktogram zmienil sie w '&'" << endl;
                        }
                        cout << "Wprowadziles d" << endl;
                    }
                    else
                        cout << "Nie moge wejsc w sciane!" << endl;
                }
                break;
            case 'q':
            case 'Q':
                cout << "Wprowadziles q, powracam do menu" << endl;
                break;
            default:
                cout << "Wprowadziles zly klawisz" << endl;
                break;
            }
        }

        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                cout << mapy[nr_mapy][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;

        bool temp; // temp utworzony po to żeby nie wywolywac drugi raz funkcji w ifie
        temp = wygrana(mapy, nr_mapy, odblokowany_lvl);

        if (dostepne_ruchy < 0 and temp == 0)
        {
            for (int i = 0; i < 50; i++)
            {
                cout << char(254);
            }
            cout << endl;
            cout << char(254) << "Wykorzystales dostepna liczbe ruchow. PRZEGRALES" << char(254) << endl;
            for (int i = 0; i < 50; i++)
            {
                cout << char(254);
            }
            cout << endl;
            cout << "Jesli chcesz ponownie sprobowac swoich sil, powroc do MENU" << endl;
        }

        if (ruch == 'Q' or ruch == 'q')
        {
            system("cls");
            rozgrywka(mapa_przekazywana, menu(odblokowany_lvl), mapy, odblokowany_lvl);
        }
    }
}
bool wygrana(char mapy[4][mapaY][mapaZ], int nr_mapy, int* odblokowany_lvl)
{
    int ilosc_skrzynek = 0;
    for (int i = 0; i < mapaY; i++)
    {
        for (int j = 0; j < mapaZ; j++)
            if (mapy[nr_mapy][i][j] == 'S')
            {
                ilosc_skrzynek++;
                break;
            }
    }
    if (ilosc_skrzynek == 0)
    {
        *odblokowany_lvl = maks(odblokowany_lvl, nr_mapy + 1);
        cout << "Poziom wygrany" << endl;
        if (*(odblokowany_lvl)+1 > 4)
            cout << "Przeszedles cala gre, gratulacje uzytkowniku. Mozesz ponownie rozegrac poziomy" << endl;
        else
            cout << "Odblokowales " << (*(odblokowany_lvl)+1) << "Poziom" << endl; //licze poziomow uzytkownik liczy od 1
        return 1;
    }
    return 0;

}

int main()
{
    int odblokowany_lvl = 0;
    ekran_powitalny();

    cout << "WASD - poruszanie sie  Q - powrot do menu glownego" << endl;

    char mapy[4][mapaY][mapaZ] =
    {
     {
         {char(19), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
         {'#', '_', '_', '_', '_', '_', 'X', '#', '#', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', 'S', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '#', '_', '#', '_', '@', '_', '_', '_', '#'},
         {'#', '#', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '#', '#', '_', '_', 'S', '_', '_', '_', '#'},
         {'#', '#', '#', '_', '_', '_', '_', '_', 'X', '#'},
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} },

     {
         {char(33), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '_', 'S', '_', '_', '_', 'X', '_', '_', '#'},
         {'#', 'X', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '@', '_', '_', '_', '#'},
         {'#', 'S', '_', '_', '_', '_', '_', '_', 'X', '#'},
         {'#', '_', '_', '_', '_', 'S', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} },

     {
         {char(30), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '_', 'S', '#', '_', '#'},
         {'#', '_', 'X', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '@', '_', '_', '_', '#'},
         {'#', '#', '_', '_', '_', '_', '_', '_', 'X', '#'},
         {'#', '#', '_', '_', '_', 'S', '_', '_', '_', '#'},
         {'#', '#', '#', '_', '_', '_', '_', '_', '_', '#'},
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} },

     {
         {char(39), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
         {'#', '#', '_', '_', '#', '_', '_', '_', '#', '#'},
         {'#', '_', 'X', '_', '#', '_', 'S', '#', '_', '#'},
         {'#', '_', '_', '_', '#', '_', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '_', '_', 'S', '_', '#'},
         {'#', '_', '_', '_', '_', '@', '_', '_', '_', '#'},
         {'#', '_', '_', '_', '_', '_', '_', '_', 'X', '#'},
         {'#', 'X', '_', '_', '_', 'S', '_', '_', '_', '#'},
         {'#', '#', '_', '_', '_', '_', '_', '_', '#', '#'},
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} }
    };
    char mapy_do_przekazywania[4][mapaY][mapaZ] =
    {
      {
          {char(19), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
          {'#', '_', '_', '_', '_', '_', 'X', '#', '#', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', 'S', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '#', '_', '#', '_', '@', '_', '_', '_', '#'},
          {'#', '#', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '#', '#', '_', '_', 'S', '_', '_', '_', '#'},
          {'#', '#', '#', '_', '_', '_', '_', '_', 'X', '#'},
          {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} },

      {
          {char(33), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '_', 'S', '_', '_', '_', 'X', '_', '_', '#'},
          {'#', 'X', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '@', '_', '_', '_', '#'},
          {'#', 'S', '_', '_', '_', '_', '_', '_', 'X', '#'},
          {'#', '_', '_', '_', '_', 'S', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} },

      {
          {char(30), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '_', 'S', '#', '_', '#'},
          {'#', '_', 'X', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '@', '_', '_', '_', '#'},
          {'#', '#', '_', '_', '_', '_', '_', '_', 'X', '#'},
          {'#', '#', '_', '_', '_', 'S', '_', '_', '_', '#'},
          {'#', '#', '#', '_', '_', '_', '_', '_', '_', '#'},
          {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} },

      {
          {char(39), '#', '#', '#', '#', '#', '#', '#', '#', '#'},
          {'#', '#', '_', '_', '#', '_', '_', '_', '#', '#'},
          {'#', '_', 'X', '_', '#', '_', 'S', '#', '_', '#'},
          {'#', '_', '_', '_', '#', '_', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '_', '_', 'S', '_', '#'},
          {'#', '_', '_', '_', '_', '@', '_', '_', '_', '#'},
          {'#', '_', '_', '_', '_', '_', '_', '_', 'X', '#'},
          {'#', 'X', '_', '_', '_', 'S', '_', '_', '_', '#'},
          {'#', '#', '_', '_', '_', '_', '_', '_', '#', '#'},
          {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} }
    };
    rozgrywka(mapy, menu(&odblokowany_lvl), mapy_do_przekazywania, &odblokowany_lvl);

}