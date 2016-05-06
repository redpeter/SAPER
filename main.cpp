#include "plansza.h"
#include <iostream>

int main(int argc, char**argv)
{
	struct pole test;
	test.wartosc = 1;
	test.odkryte = true;
	cout << test.wartosc << " " << test.odkryte;
	struct pole** wsk;
	wsk = createArray(14, 15);
	if (wsk == NULL) cout << "Problem\n";
	Random(wsk, 14, 15, 10);
	Write(wsk, 14, 15);
	Count(wsk, 14, 15);
	deleteArray(&wsk, 14);

	return 0;
}

