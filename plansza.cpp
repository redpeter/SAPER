#include "plansza.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void DeleteArray(pole ***pArray, int row)
{
	for(int i=0; i<row; i++)
		delete[] (*pArray)[i];
	delete[] *pArray;
	*pArray = NULL;
}

struct pole **CreateArray(int row, int col)
{
	//dynamiczna alokacja pamieci
  	struct pole **tab=new struct pole *[row];
  	if(tab == NULL)
    	return NULL;
 	for(int i=0; i<col; i++){
   		tab[i]=new struct pole [col];
    	if(tab[i] == NULL){
      		DeleteArray(&tab, i);
      		return NULL;
    	}
  	}
  	//nadanie poczatkowych wartosci
  	for(int j=0; j<row; j++){
  		for(int k=0; k<col; k++){
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
	if (src == NULL){
		cout << "Problem z odczytaniem tablicy.\n";
	}
	else{
		for (i=0; i<row; i++){
			for (j=0; j<col; j++) {
				if (src[i][j].wartosc == BOMB)
					cout << "*";
				else{
				    if (src[i][j].wartosc == 0)
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

void Random(pole **scr, int row, int col, int bombs)
{
	if(scr==NULL){
		cout << "Problem z odczytaniem tablicy.\n";
		return;
	}
	srand(time(NULL));
	int x, y;
	while(bombs>0){
		x=(rand() % row);
		y=(rand() % col);
		if((scr[x][y]).wartosc != BOMB){
			(scr[x][y]).wartosc = BOMB;
			--bombs;
		}
	}
	return;
}

int Count(pole **src, int row, int col)
{
	int i, j, ile=0;
	for (i=0; i<row; i++){
		for (j=0; j<col; j++){
			if (src[i][j].wartosc == BOMB) ile++;
		}
	}
	cout << "\nNa planszy pozostalo " << ile << " bomb.\n";
	return ile;
}

void Test(int row, int col, int bomb)
{
	struct pole** tab;
	tab = CreateArray(row, col);
	if (tab == NULL)
        cout << "Problem\n";
	Random(tab, row, col, bomb);
	Write(tab, row, col);
	Count(tab, row, col);
	DeleteArray(&tab, row);
}
