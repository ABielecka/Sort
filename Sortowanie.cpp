#include "Sorts.h"
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

void wyswietl_tab(int *tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << tab[i] << ",";
	}
	cout << endl << endl;
}

//Funkcja sprawdza czy tabela jest dobrze posortowana
void sprawdz_sortowanie(int *tab, int size, bool descending)
{
	for (int i = 0; i < size-1; i++)
	{
		if (descending) 
		{
			if (tab[i] < tab[i+1]) {
				cout << "Zle posortowano" << endl << endl;
				break;
			}
		}
		else 
		{
			if (tab[i] > tab[i + 1]) {
				cout << "Zle posortowano" << endl << endl;
				break;
			}
		}
	}
}

void wypelnij_tabele(int *tab, int size, float procent)
{
	int liczba_posortowanych;
	if (procent < 0) {
		//Pozycje losowe
		for (int i = 0; i < size; i++) {
			tab[i] = (rand() % 100);
		}
		//Posortowane malejaco
		Sorts::QuickSort<int>(tab, 0, size - 1, true);
	}
	else if (procent > 0) {
		liczba_posortowanych = (int)((size * procent) / 100);
		int *posortowane;
		posortowane = new int[liczba_posortowanych];

		//Pozycje posortowane
		for (int i = 0; i < liczba_posortowanych; i++) {
			posortowane[i] = rand() % 100;
		}
		Sorts::QuickSort<int>(posortowane, 0, liczba_posortowanych - 1, false);

		//Pierwsze posortowane
		for (int i = 0; i < liczba_posortowanych; i++) {
			tab[i] = posortowane[i];
		}

		//Pozostałe pozycje losowe
		for (int i = liczba_posortowanych; i < size; i++) {
			tab[i] = 101 + (rand() % 100);
		}

		delete[] posortowane;
	}
	else { //procent posortowanych równy 0 - liczby pseudolosowe   
		for (int i = 0; i < size; i++) {
			tab[i] = (rand() % 100);
		}
	}
}

void sortuj(int *tab, int n, int algorytm, int liczbaSort)
{
	float procentPosortowanych[] = { 0,25,50,75,95,99,99.7,-1 };
	clock_t StartTime, StopTime;
	double czas;
	ofstream plik;
	int maxDepth;

	int minCzas, maxCzas;
	double sortCzas;

	switch (algorytm)
	{
	case 1:
		plik.open("QuickSort.txt", ios::app);

		for (float  posortpowanych : procentPosortowanych)
		{
			sortCzas = 0;
			minCzas = 1000000;
			maxCzas = -1;

			plik << "Rozmiar tablicy: " << n << "  Procent posortowanych:  " << posortpowanych << endl << endl;

			for (int i = 0; i < liczbaSort; i++)
			{
				wypelnij_tabele(tab, n, posortpowanych);

				StartTime = clock();
				Sorts::QuickSort<int>(tab, 0, n - 1, false);
				StopTime = clock();

				czas = ((double)(StopTime - StartTime) / CLOCKS_PER_SEC)*1000;

				plik << czas << endl;

				sortCzas = sortCzas + czas;

				if (czas < minCzas) minCzas = czas;
				if (czas > maxCzas) maxCzas = czas;

				//wyswietl_tab(tab, n);
				sprawdz_sortowanie(tab, n, false);
			}
			plik << endl;

			plik << "Min czas     - " << minCzas << endl;
			plik << "Max czas     - " << maxCzas << endl;
			plik << "Sredni czas  - " << sortCzas / liczbaSort << endl;

			plik << endl << endl;
		}

		plik.close();
		break;
	case 2:
		plik.open("MergeSort.txt", ios::app);

		for (float posortpowanych : procentPosortowanych)
		{
			sortCzas = 0;
			minCzas = 1000000;
			maxCzas = -1;

			plik << "Rozmiar tablicy: " << n << "  Procent posortowanych:  " << posortpowanych << endl << endl;

			for (int i = 0; i < liczbaSort; i++)
			{
				wypelnij_tabele(tab, n, posortpowanych);

				StartTime = clock();
				Sorts::MergeSort<int>(tab, 0, n - 1, false);
				StopTime = clock();

				czas = ((double)(StopTime - StartTime) / CLOCKS_PER_SEC) * 1000;

				plik << czas << endl;

				sortCzas = sortCzas + czas;

				if (czas < minCzas) minCzas = czas;
				if (czas > maxCzas) maxCzas = czas;

				//wyswietl_tab(tab, n);
				sprawdz_sortowanie(tab, n, false);
			}
			plik << endl;

			plik << "Min czas     - " << minCzas << endl;
			plik << "Max czas     - " << maxCzas << endl;
			plik << "Sredni czas  - " << sortCzas / liczbaSort << endl;

			plik << endl << endl;
		}

		plik.close();
		break;
	case 3:
		plik.open("IntrospectiveSort.txt", ios::app);

		maxDepth = 2 * log(n) / log(2);

		for (float posortpowanych : procentPosortowanych)
		{
			sortCzas = 0;
			minCzas = 1000000;
			maxCzas = -1;

			plik << "Rozmiar tablicy: " << n << "  Procent posortowanych:  " << posortpowanych << endl << endl;

			for (int i = 0; i < liczbaSort; i++)
			{
				wypelnij_tabele(tab, n, posortpowanych);

				StartTime = clock();
				Sorts::IntroSort<int>(tab, 0, n - 1, maxDepth, false);
				StopTime = clock();

				czas = ((double)(StopTime - StartTime) / CLOCKS_PER_SEC) * 1000;

				sortCzas = sortCzas + czas;

				if (czas < minCzas) minCzas = czas;
				if (czas > maxCzas) maxCzas = czas;

				plik << czas << endl;

				//wyswietl_tab(tab, n);
				sprawdz_sortowanie(tab, n, false);
			}
			plik << endl;

			plik << "Min czas     - " << minCzas << endl;
			plik << "Max czas     - " << maxCzas << endl;
			plik << "Sredni czas  - " << sortCzas / liczbaSort << endl;

			plik << endl << endl;
		}

		plik.close();
		break;
	default:
		break;
	}
}

int main()
{
	int n = 0;		//rozmiar tablicy
	int al;			//algorytm sortowania
	int ls;                 //liczba sortowan (liczba tabel z danymi)
	int *tablica;		//tablica zawierajaca liczby

	srand(time(NULL));      //Funkcja ustawia punkt startowy, który jest stosowany do generowania serii pseudo losowych liczb calkowitych.
				//Funkcja rand bedzie generowala zawsze ta sama sekwencje liczb, jezeli nie zostanie wywolana wczesniej funkcja srand, 
	                        //lub funkcja srand zostanie wywolana z argumentem równym 1.

	do
	{
		cout << "Wybierz algorytm sortowania:" << endl
			<< "1 Quick Sort" << endl
			<< "2 Merge Sort" << endl
			<< "3 Introspective Sort" << endl
			<< "0 exit" << endl << endl;
		cin >> al;

		if (al != 0)
		{
			cout << "Podaj rozmiar tablicy: ";
			cin >> n;

			cout << "Podaj liczbe sortowan: ";
			cin >> ls;
			cout << endl;

			tablica = new int[n];
				
			sortuj(tablica, n, al, ls);

			delete[] tablica;

			cout << "\nZapisano \n\n" << endl << endl;
		}

	} while (al != 0);

	return 0;
}
