// LAB2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>  //Wektor, kontener
#include <fstream>  //Do obs³ugi plików
#include <iostream> //cin cout
#include <string>


using namespace std;

class Zadanie {
public:
	int terminDostepnosci;  //r
	int czasObslugiZad;		//p
	int czasDostarczaniaZad;//q
};


int main()
{
	std::vector<Zadanie> dane;	 //Tutaj beda sie znajdowac wczytane dane z pliku
	std::fstream file;			 //Plik z danymi.

	string fileName;			//Nazwa pliku do ktorego zostana wczytane dane
	std::cout << "\nPodaj nazwe pliku: ";
	//std::cin >> fileName;
	fileName = "SCHRAGE1.dat";
	std::cout << "Nazwa pliku " << fileName << endl;
	file.open(fileName, std::ios::in);

	unsigned int liczbaZadan;	//format pliku: n  r p q r p q ...


	if (file.good() == true) {
		Zadanie obiektTmp;		//obiekt tymczasowy do wrzucania danych do wektora


		file >> liczbaZadan;	 //odczytuje z pliki pierwsza linijke - ile zadan

		for (int i = 0; i < liczbaZadan; i++) {
			file >> obiektTmp.terminDostepnosci;		//wczytanie r
			file >> obiektTmp.czasObslugiZad;			//wczytanie p
			file >> obiektTmp.czasDostarczaniaZad;	//wcyztanie q   --- drugie zad 
			dane.push_back(obiektTmp);					//wrzucenie calego obiektu na koniec
		}
			//*****WYSWIETLANIE WCZYTANYCH DANYCH*****
		cout << "Liczba zad: " <<liczbaZadan << endl;
		cout << "Wczytane dane: \n";
		cout << liczbaZadan << endl;
		for (int i = 0; i < liczbaZadan; i++)
		{
		cout << dane[i].terminDostepnosci;
		cout << " " << dane[i].czasObslugiZad;
		cout << " " << dane[i].czasDostarczaniaZad << endl;
		}
		

		file.close();		//zamkniecie pliku
	}
	else cout << "Nie mozna wczytac pliku" << std::endl;

	getchar();
	return 0;
}

