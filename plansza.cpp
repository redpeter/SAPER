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
				if (src[i][j].wartosc == BOMB&&src[i][j].odkryte == true)
					cout << "*";
				else{
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
	if(src==NULL){
		cout << "Problem z odczytaniem tablicy.\n";
		return;
	}
	srand(time(NULL));
	int x, y;
	while(bombs>0){
		x=(rand() % row);
		y=(rand() % col);
		if((src[x][y]).wartosc != BOMB){ //sprawdzamy czy juz nie ma bomby
			(src[x][y]).wartosc = BOMB; //wstawiamy bombe w wylosowane pole
			int r, c;
			for(r=-1; r<=1; r++){
				for(c=-1; c<=1; c++){
					if((x + r) < 0 || (y + c) < 0 || (x + r) >= row || (y + c) >= col) {
						continue; //nic bo poza brzegiem
					}
					if((src[x+r][y+c]).wartosc == BOMB){
						continue; //nic bo tutaj jest jakas mina
					}
					(src[x+r][y+c]).wartosc += 1; //zwiekszamy o 1 bo dodalismy bombe
				}
			}
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

void show(pole **src, int row, int col)
{
	int x, y;
	cout << "podaj x (od 0 do " << col-1 << "): ";
	cin >> x;
	cout << "podaj y (od 0 do " << row-1 << "): ";
	cin >> y;
	src[x][y].odkryte = true;
}

void Test(int row, int col, int bomb)
{
	struct pole** tab;
	tab = CreateArray(row, col);
	if (tab == NULL)
        cout << "Problem\n";
	Random(tab, row, col, bomb);
	int i;
	for (i = 0; i < 5; i++) {
		Write(tab, row, col);
		Count(tab, row, col);
		show(tab, row, col);
		system("cls");
	}
	DeleteArray(&tab, row);
}

