//#include "plansza.h"
#include <iostream>

using namespace std;

void deleteArray(pole ***pArray, int n)
{
	for(int i=0; i<n; i++)
		delete[] (*pArray)[i];
	delete[] *pArray;
}

struct pole** createArray(int row, int col)
{
	//dynamiczna alokacja pamieci
  	struct pole** tab=new struct pole* [row];
  	if(tab==NULL)
    	return NULL;
 	for(int i=0; i<col; i++){
   		tab[i]=new struct pole [col];
    	if(tab[i]==NULL){
      		deleteArray(&tab, i);
      		return NULL;
    	}
  	}
  	//nadanie poczatkowych wartosci
  	for(int j=0; j<row; j++){
  		for(int k=0; k<col; k++){
  			tab[j][k].wartosc=0;
  			tab[j][k].odkryte=false;
		  }
	  }
  return tab;
}
void Write(pole** src, int row, int col) 
{
	int i, j;
	cout << "\n\n";
	if (*src == NULL)
	{
		cout << "Problem z odczytaniem tablicy";
	}
	else
	{
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				cout << src[i][j];
			}
		}
	}
}





















>>>>>>> .theirs
