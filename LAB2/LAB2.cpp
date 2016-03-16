// SPD_LAB2KD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>  //Wektor, kontener
#include <fstream>  //Do obs³ugi plików
#include <iostream> //cin cout
#include <string>
#include <queue>


using namespace std;

class Zadanie {
public:
	int terminDostepnosci;  //r
	int czasObslugiZad;		//p
	int czasDostarczaniaZad;//q
};


struct PorownajQ
{
	bool operator ()(const Zadanie & zadanie1, const Zadanie & zadanie2)
	{
		//kolejnoœæ - malejco
		if (zadanie1.czasDostarczaniaZad > zadanie2.czasDostarczaniaZad) return false;

		if (zadanie1.czasDostarczaniaZad < zadanie2.czasDostarczaniaZad) return true;
		return false;
	}
};

struct PorownajR
{
	bool operator ()(const Zadanie & zadanie1, const Zadanie & zadanie2)
	{
		//kolejnoœæ - malejco
		if (zadanie1.terminDostepnosci > zadanie2.terminDostepnosci) return true;

		if (zadanie1.terminDostepnosci < zadanie2.terminDostepnosci) return false;
		return false;
	}
};


int main()
{
	std::vector<Zadanie> dane;	 //Tutaj beda sie znajdowac wczytane dane z pliku
	std::fstream file;			 //Plik z danymi.

								 //tworzymy kolejke
	priority_queue < Zadanie, vector < Zadanie >, PorownajQ > kolejkaQ; //Zbior G
	priority_queue < Zadanie, vector < Zadanie >, PorownajR > kolejkaR; //Zbior N



	string fileName;			//Nazwa pliku do ktorego zostana wczytane dane
	std::cout << "\nPodaj nazwe pliku: ";
	//std::cin >> fileName;
	fileName = "SCHRAGE9.dat";
	std::cout << "Nazwa pliku " << fileName << endl;
	file.open(fileName, std::ios::in);

	int liczbaZadan;	//format pliku: n  r p q r p q ...


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
		cout << "Liczba zad: " << liczbaZadan << endl;
		//cout << "Wczytane dane: \n";
		//cout << liczbaZadan << endl;


		for (int i = 0; i < liczbaZadan; i++)
		{
			//cout << dane[i].terminDostepnosci;
			//cout << " " << dane[i].czasObslugiZad;
			//cout << " " << dane[i].czasDostarczaniaZad << endl;
		//	kolejkaQ.push(dane[i]); //do zbioru G nie wrzucamy, ma byc pusty ale ma byc kolejka
			kolejkaR.push(dane[i]); //wrzucenie do kolejki

		}
		file.close();		//zamkniecie pliku
	}
	else cout << "Nie mozna wczytac pliku" << std::endl;

	//Algorytm Schrage
	int t, k, Cmax;
	t = k = Cmax = 0;
	//             N                     G
	while ( !(kolejkaR.empty()) || !(kolejkaQ.empty()) )
	{
		while (!(kolejkaR.empty()) && (kolejkaR.top().terminDostepnosci <= t))
			{
			//	cout << kolejkaR.top().terminDostepnosci << " ";
				kolejkaQ.push(kolejkaR.top()); //wrzucenie do kolejki cale zadanie
				kolejkaR.pop(); //wyrzucamy element ze zbioru N
			}
		if (kolejkaQ.empty()) //pkt 5, jezeli zbior G jest pusty
		{
			t = kolejkaR.top().terminDostepnosci;
			continue;
		}
		k++;
		t = t + kolejkaQ.top().czasObslugiZad;
		Cmax = max(Cmax, t + kolejkaQ.top().czasDostarczaniaZad);
		kolejkaQ.pop();
	}


	cout << "\n" << "Cmax: " << Cmax;

	getchar();
	return 0;
}