// SPD_LAB1DK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>  //Wektor, kontener
#include <fstream>  //Do obs³ugi plików
#include <iostream> //cin cout
#include <string>


using namespace std;

class Zadanie {
public :
	int terminDostepnosci;  //r
	int czasObslugiZad;		//p
	int czasDostarczaniaZad;//q
};



int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<Zadanie> dane;	 //Tutaj beda sie znajdowac wczytane dane z pliku
	std::fstream file;			 //Plik z danymi.

	string fileName;			//Nazwa pliku do ktorego zostana wczytane dane
	std::cout << "\nPodaj nazwe pliku: ";
	//std::cin >> fileName;
	fileName = "JACK7.dat";
	std::cout << "Nazwa pliku " << fileName << endl;
	file.open(fileName, std::ios::in);

	unsigned int liczbaZadan;	//format pliku: n  r p q r p q ...


	if (file.good() == true) {
		Zadanie obiektTmp;		//obiekt tymczasowy do wrzucania danych do wektora

	
		file >> liczbaZadan;	 //odczytuje z pliki pierwsza linijke - ile zadan
		
		for (int i = 0; i < liczbaZadan; i++) {
			file >> obiektTmp.terminDostepnosci;		//wczytanie r
			file >> obiektTmp.czasObslugiZad;			//wczytanie p
			//file >> obiektTmp.czasDostarczaniaZad;	//wcyztanie q   --- drugie zad 
			dane.push_back(obiektTmp);					//wrzucenie calego obiektu na koniec
		}
		/*	//*****WYSWIETLANIE WCZYTANYCH DANYCH*****
		cout << "Liczba zad: " <<liczbaZadan << endl;	
		cout << "Wczytane dane: \n";					
		cout << liczbaZadan << endl;
			for (int i = 0; i < liczbaZadan; i++) 
		{
			cout << dane[i].terminDostepnosci;
			cout << " " << dane[i].czasObslugiZad << endl;
		}
		*/

		int *C = new int[liczbaZadan+1];
		C[0]=0;
		int *pi = new int[liczbaZadan+1];
		for(int i = 0; i <=liczbaZadan; i++)
			pi[i]=i;

		// Sortowanie vektora z danymi wedlug terminDostepnosci (r)
		Zadanie tym;
		for(int i=0; i<liczbaZadan-1; i++) 
		{
			for(int j = 0; j<liczbaZadan-1; j++)
			{
				if ( dane[j].terminDostepnosci > dane[j+1].terminDostepnosci )
				{
					tym = dane[j];
					dane[j] = dane[j+1];
					dane[j+1] = tym;
				}
			}
		}

		//wsywietlanie po sortowaniu
		/*
		for (int i = 0; i < liczbaZadan; i++) 
		{
			cout << dane[i].terminDostepnosci;
			cout << " " << dane[i].czasObslugiZad << endl;
		}
		*/


		//obliczanie cmax
		for(int i = 1; i <= liczbaZadan; i++) 
		{
			C[pi[i]] = C[pi[i-1]] >= dane[pi[i]-1].terminDostepnosci ? C[pi[i-1]] + dane[pi[i]-1].czasObslugiZad: dane[pi[i]-1].terminDostepnosci + dane[pi[i-1]].czasObslugiZad;
		}

		cout << "Cmax = " << C[liczbaZadan]<<endl;

		file.close();		//zamkniecie pliku
	}
	else cout << "Nie mozna wczytac pliku" << std::endl;

	getchar();
    return 0;
}

