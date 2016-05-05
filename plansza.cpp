#include "plansza.h"
#include <iostream>

using namespace std;

void deleteArray(pole ***pArray, int n)
{
	for(int i=0; i<n; i++)
		delete[] (*pArray)[i];
	delete[] *pArray;
}
