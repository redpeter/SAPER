#ifndef PLANSZA_H
#define PLANSZA_H
#define BOMB 9

using namespace std;

struct pole {
	int wartosc;
	bool odkryte;
};

void deleteArray(pole ***, int);
struct pole** createArray(int, int);
void Write(pole **, int, int);
void Random(pole **, int, int, int);
int Count(pole**, int, int);
#endif

