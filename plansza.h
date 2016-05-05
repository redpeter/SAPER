#ifndef PLANSZA_H
#define PLANSZA_H

using namespace std;

struct pole {
	int wartosc;
	bool odkryte;
};

void deleteArray(pole ***, int);
struct pole** createArray(int, int);
#endif
