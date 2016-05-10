#ifndef PLANSZA_H
#define PLANSZA_H
#define BOMB 9

using namespace std;

struct pole {
	int wartosc;
	bool odkryte;
};

void DeleteArray(pole ***, int);
struct pole** CreateArray(int, int);
void Write(pole **, int, int);
void Random(pole **, int, int, int);
int CountBombs(pole**, int, int);
bool IsWin(pole**, int, int);
bool Show(pole **, int, int);
void Menu();
void Test(int, int, int);
int IfBomb(pole**, int, int);

#endif