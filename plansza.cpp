#include "plansza.h"
#include <iostream>
#include <cstdlib>
#include <ctime> //do losowania liczb
#include <conio.h> //obsluga klawiszy

/*Usuwa tablice 2D*/
void DeleteArray(pole ***pArray, int row)
{
	for (int i = 0; i<row; i++)
		delete[](*pArray)[i];
	delete[] * pArray;
	*pArray = NULL;
}

/*Tworzy tablice 2D, inicjuje ja wartosciami 0 i false */
struct pole **CreateArray(int row, int col)
{
	//dynamiczna alokacja pamieci
	struct pole **tab = new struct pole *[row];
	if (tab == NULL)
		return NULL;
	for (int i = 0; i<row; i++) {
		tab[i] = new struct pole[col];
		if (tab[i] == NULL) {
			DeleteArray(&tab, i);
			return NULL;
		}
	}
	//nadanie poczatkowych wartosci
	for (int j = 0; j<row; j++) {
		for (int k = 0; k<col; k++) {
			tab[j][k].wartosc = 0;
			tab[j][k].odkryte = false;
		}
	}
	return tab;
}

/*Wypisuje plansze na ekran */
void Write(pole** src, int row, int col, int y, int x)
{
	cout << "\n\n";
	if (src == NULL) {
		cout << "Problem z odczytaniem tablicy.\n";
	}
	else {
		for (int i = 0; i < col+2; i++) { // ramka
			cout << "-";
		}
		cout << endl;
		
		for (int i = 0; i<row; i++) {
			cout << "|"; // ramka
			for (int j = 0; j<col; j++) {
				if (src[i][j].wartosc == BOMB && src[i][j].odkryte == true)
					cout << "*";
				else {
					if (src[i][j].odkryte == false && (i!=y || j!=x))
						cout << "#";
					else if (src[i][j].odkryte == false && (i==y && j==x))		//pytajnik, zeby widziec gdzie jestesmy
						cout << "?";
                    else if (src[i][j].odkryte == false && src[i][j].flaga == true)      //wyswietlanie choragiewek jako wykrzyknik
                        cout << "!";
					else if (src[i][j].wartosc == 0)
						cout << " ";
					else
						cout << src[i][j].wartosc;
				}
			}
			cout << "|\n"; // ramka
		}
		
		for (int i = 0; i < col+2; i++) {
			cout << "-";
		}
		cout << endl;
	}
	return;
}

/*Rozmieszcza losowo zadana liczbe bomb na planszy */
void Random(pole **src, int row, int col, int bombs)
{
	if (src == NULL) {
		cout << "Problem z odczytaniem tablicy.\n";
		return;
	}
	srand(time(NULL));
	int x, y;
	while (bombs>0) {
		x = (rand() % row);
		y = (rand() % col);
		if ((src[x][y]).wartosc != BOMB) { //sprawdzamy czy juz nie ma bomby
			(src[x][y]).wartosc = BOMB; //wstawiamy bombe w wylosowane pole
			int r, c;
			for (r = -1; r <= 1; r++) {
				for (c = -1; c <= 1; c++) {
					if ((x + r) < 0 || (y + c) < 0 || (x + r) >= row || (y + c) >= col) {
						continue; //nic bo poza brzegiem
					}
					if ((src[x + r][y + c]).wartosc == BOMB) {
						continue; //nic bo tutaj jest jakas mina
					}
					(src[x + r][y + c]).wartosc += 1; //zwiekszamy o 1 bo dodalismy bombe
				}
			}
			--bombs;
		}
	}
	return;
}

/*Zlicza bomby i wypisuje ich liczbe na ekran
Zwraca liczbe bomb na planszy */
int CountBombs(pole **src, int row, int col)
{
	int i, j, ile = 0;
	for (i = 0; i<row; i++) {
		for (j = 0; j<col; j++) {
			if (src[i][j].wartosc == BOMB) ile++;
//			if (src[i][j].wartosc == BOMB && src[i][j].odkryte == false) ile++;
//jak juz odkryjemy jakas bombe to i tak jest po ptakach...
//po odkryciu bomby blednie zliczaloby bomby. w takiej wersji zliczanie flag
		}
	}
	cout << "\nNa planszy pozostalo " << ile << " bomb.\n";
	return ile;
}

/*Sprawdza, czy nastapila juz wygrana */
bool IsWin(pole **src, int row, int col)
{
	bool win = false;
	int zakryte = 0;
	for (int i = 0; i<row; i++) {
		for (int j = 0; j<col; j++) {
			if (src[i][j].odkryte == false) {
				zakryte++;
			}
		}
	}
	int bombs = CountBombs(src, row, col);
	if (zakryte == bombs) {
		win = true;
		system("cls");
		cout << "\n";
		cout << "Gratulacje, wygrana!";
	}
	return win;
}

/*Sprawdza, czy odkryto bombe, czysci ekran
i informuje uzytkownika o ewentualnej przegranej.*/
bool IfBomb(pole**src, int row, int col, int y, int x) {
	if (src[y][x].wartosc == BOMB) {
		system("cls");

//Po co wywoluje te funkcje?
//		Write(src, row, col, y, x);
//		CountBombs(src, row, col);
//		cout << endl << endl;
		cout << "Odkryles bombe, koniec gry!";
		return true;
	}
	return false;
	/*	int i = IfBomb(src, y, x);   // fragment wyciety z show
	if (i == -1) {
	Write(src, row, col, y, x);
	CountBombs(src, row, col);
	cout << endl << endl;
	*/
}


/*Rekurencyjnie odkrywa sasiadow pustego pola */
void ShowNeighbour(pole **src, int row, int  col, int y, int x)
{
	//UWAGA - 'puste' pole nigdy nie sasiaduje z bomba!
	for (int r = -1; r <= 1; r++) {
		for (int c = -1; c <= 1; c++) {
			if (r == 0 && c == 0) //obecne pole - juz odkryte
				c++;
			if ((y + r) < 0 || (x + c) < 0 || (y + r) >= row || (x + c) >= col) {
				continue; //brzeg
			}
			if (src[y + r][x + c].wartosc != 0 && src[y + r][x + c].odkryte == false) { //odkryj niepuste
				src[y + r][x + c].odkryte = true;
			}
			if (src[y + r][x + c].wartosc == 0 && src[y + r][x + c].odkryte == false) { //dla pustych rekurencja - odkrywaj dalej
				src[y + r][x + c].odkryte = true;
				ShowNeighbour(src, row, col, y + r, x + c);
			}
		}
	}
}



/*Pobiera od usera pole do odkrycia i odkrywa je

void ShowCell(pole **src, int row, int col, int &y, int &x)
{
	cout << "podaj x (od 0 do " << col - 1 << "): ";
	cin >> x;
	cout << "podaj y (od 0 do " << row - 1 << "): ";
	cin >> y;
	src[y][x].odkryte = true;

	if (src[y][x].wartosc == 0) {
		ShowNeighbour(src, row, col, y, x);
	}
}
*/

void PressKey(pole **src, int row, int col, int &y, int &x)
{
	bool walk = true; 	//warunek dokad "chodzimy" po planszy
	int code;			//zmienna przetrzymujaca kod danego klawisza
	while(walk){
		cout << "Jestes na polu: (" << x << ", " << y << ") " << endl;
		code = getch();				//pobranie kodu wcisnietego klawisza (funkcja ta jest dostepna w bibliotece conio.h)
		switch (code){
			case 13:				//nacisniecie entera
				src[y][x].odkryte = true;
				if (src[y][x].wartosc == 0)
					ShowNeighbour(src, row, col, y, x);
				walk = false;		//koniec chodzenia, czas sprawdzic, czy to bomba, czy wygrana
				break;
			case 224:				//nacisniecie znaku specjalnego
				code = getch();
				switch (code){
					case 72:		//strzalka w gore
						if(y>0)
							y--;
						break;
					case 80:		//strzalka w dol
						if(y<row-1)
							y++;
						break;
					case 75:		//strzalka w lewo
						if(x>0)
							x--;
						break;
					case 77:		//strzalka w prawo
						if(x<col-1)
							x++;
						break;
				}
				system("cls");		//chodzimy dalej...
				Write(src, row, col, y, x);
				CountBombs(src, row, col);
				break;
		}
	}
}

void Test(int row, int col, int bomb, int &y, int &x)
{
	struct pole** tab;
	tab = CreateArray(row, col);
	if (tab == NULL)
		cout << "Problem\n";
	Random(tab, row, col, bomb);
	bool wygrana = IsWin(tab, row, col);
	bool bomba = false;
	while (1) { // lub trafiles na bombe - tez koniec
		Write(tab, row, col, y, x);
		CountBombs(tab, row, col);
		//ShowCell(tab, row, col, y, x);
		PressKey(tab, row, col, y, x);
		bomba = IfBomb(tab, row, col, y, x);
		if (bomba == true) {
			Write(tab, row, col, y, x);
			x=0;
			y=0;
			break;
		}
		wygrana = IsWin(tab, row, col);
		if(wygrana == true){
			x=0;
			y=0;
            Write(tab, row, col, y, x);
            cout<<"\n";
			break;
		}
		system("cls");
	}
	DeleteArray(&tab, row);
}

void Menu()
{
	int poziom, row, col, bomby, x=0, y=0;
	while (1>0) {
		cout << "\nWybierz poziom gry: \n";
		cout << "1. Poczatkujacy.\n";
		cout << "2. Sredniozaawansowany.\n";
		cout << "3. Ekspert.\n";
		cout << "4. Niestandardowy.\n\n";
		cout << "0. Wyjscie z gry.\n\n";
		cin >> poziom;
		switch (poziom) {
		case 0:
			cout << "Dziekujemy za wspolna zabawe.";
			return;
		case 1:
			row = col = 8;
			bomby = 10;
			Test(row, col, bomby, y, x);
			break;
		case 2:
			row = col = 16;
			bomby = 40;
			Test(row, col, bomby, y, x);
			break;
		case 3:
			row = 16;
			col = 30;
			bomby = 99;
			Test(row, col, bomby, y, x);
			break;
		case 4:
			cout << "Podaj wymiary Twojej tablicy.\nLiczba wierszy: \n";
			cin >> row;
			cout << "Liczba kolumn: \n";
			cin >> col;
			cout << "Teraz podaj liczbe bomb. Musi ona byc mniejsza od " << row*col << " .\n";
			cin >> bomby;
			Test(row, col, bomby, y, x);
			break;
		default:
			system("cls");
			cout << "Ups. Nieprawidlowy wybor. Wybierz cyfre od 0 do 4.\n";
			break;
		}
	}
}
