#include "plansza.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


void DeleteArray(pole ***pArray, int row)
{
	for (int i = 0; i<row; i++)
		delete[](*pArray)[i];
	delete[] * pArray;
	*pArray = NULL;
}

struct pole **CreateArray(int row, int col)
{
	//dynamiczna alokacja pamieci
	struct pole **tab = new struct pole *[row];
	if (tab == NULL)
		return NULL;
	for (int i = 0; i<col; i++) {
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

void Write(pole** src, int row, int col)
{
	int i, j;
	cout << "\n\n";
	if (src == NULL) {
		cout << "Problem z odczytaniem tablicy.\n";
	}
	else {
		for (i = 0; i<row; i++) {
			for (j = 0; j<col; j++) {
				if (src[i][j].wartosc == BOMB && src[i][j].odkryte == true)
					cout << "*";
				else {
					if (src[i][j].odkryte == false)
						cout << "#";
					else if (src[i][j].wartosc == 0)
						cout << " ";
					else
						cout << src[i][j].wartosc;
				}
			}
			cout << "\n";
		}
	}
	return;
}

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

int CountBombs(pole **src, int row, int col)
{
	int i, j, ile = 0;
	for (i = 0; i<row; i++) {
		for (j = 0; j<col; j++) {
			if (src[i][j].wartosc == BOMB && src[i][j].odkryte == false) ile++;
		}
	}
	cout << "\nNa planszy pozostalo " << ile << " bomb.\n";
	return ile;
}

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
		cout << "Gratulacje!";
	}
	return win;
}

/*Sprawdza, czy odkryto bombe.*/
bool IfBomb(pole**src, int row, int col, int y, int x) {
	if (src[y][x].wartosc == BOMB) {
		system("cls");

//Po co wywoluje te funkcje?
//		Write(src, row, col);
//		CountBombs(src, row, col);
//		cout << endl << endl;
		cout << "Odkryles bombe, koniec gry!";
		return true;
	}
	return false;
	/*	int i = IfBomb(src, y, x);   // fragment wyciety z show
	if (i == -1) {
	Write(src, row, col);
	CountBombs(src, row, col);
	cout << endl << endl;
	*/
}

void ShowNeighbour(pole **src, int row, int  col, int y, int x)
{
	for (int r = -1; r <= 1; r++) {
		for (int c = -1; c <= 1; c++) {
			if (r == 0 && c == 0)
				c++;
			if ((y + r) < 0 || (x + c) < 0 || (y + r) >= row || (x + c) >= col) {
				continue; //brzeg
			}
			if (src[y + r][x + c].wartosc != 0 && src[y + r][x + c].odkryte == false) {
				src[y + r][x + c].odkryte = true;
			}
			if (src[y + r][x + c].wartosc == 0 && src[y + r][x + c].odkryte == false) {
				src[y + r][x + c].odkryte = true;
				ShowNeighbour(src, row, col, y + r, x + c);
			}
		}
	}
}

void Show(pole **src, int row, int col, int &y, int &x)
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
		Write(tab, row, col);
		CountBombs(tab, row, col);
		Show(tab, row, col, y, x);
		bomba = IfBomb(tab, row, col, y, x);
		if (bomba == true) {
			Write(tab, row, col);
			break;
		}
		wygrana = IsWin(tab, row, col);
		if(wygrana == true) break;
		system("cls");
	}
	DeleteArray(&tab, row);
}

void Menu()
{
	int poziom, row, col, bomby, x, y;
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
			row = 30;
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
