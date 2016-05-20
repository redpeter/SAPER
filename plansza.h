#ifndef PLANSZA_H
#define PLANSZA_H
#define BOMB 9

using namespace std;

struct pole {
	int wartosc;
	bool odkryte;
	bool flaga;
};

void DeleteArray(pole ***, int);
struct pole** CreateArray(int, int);
void Write(pole **, int, int, int, int);
void Random(pole **, int, int, int);
int CountFlags(pole**, int, int, int);
bool IsWin(pole**, int, int, int);
bool IfBomb(pole**, int, int, int, int);
//void ShowCell(pole **, int, int, int&, int&);
void PressKey(pole, int, int, int, int&, int&, int&);
void ShowNeighbour(pole **, int, int, int, int, int&);
void Test(int, int, int, int&, int&);
void Menu();

#endif

