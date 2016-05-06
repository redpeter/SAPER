#ifndef PLANSZA_H
#define PLANSZA_H

using namespace std;

struct pole {
	int wartosc;
	bool odkryte;
};

void deleteArray(pole ***, int);
struct pole** createArray(int, int);
void Write(pole **, int, int);
void random(pole **, int, int, int);
int Count(pole**, int, int);
#endif
