#ifndef SORTS_H
#define SORTS_H

#include <memory>
//#include <cmath>

using namespace std;

class Sorts {
private:

	// funkcje dla QuickSort
	template <typename T>
	static int QuickSort_Split(T *tab, int left, int right, bool descending);

	// funkcje dla MergeSort
	template <typename T>
	static void Merge(T *tab, int left, int middle, int right, bool descending);

	// funkcje dla HeapSort
	static int parentId(int n);
	static int leftChildId(int n);
	static int rightChildId(int n);
	template <typename T>
	static void BudujKopiec(T *tab, int size, bool descending);
	template <typename T>
	static void KopcujMax(T *tab, int i, int size);
	template <typename T>
	static void KopcujMin(T *tab, int i, int size);

	Sorts() {};

public:
	/* QuickSort                                                             */
	/* na podstwie algorytmu z wykladu                                       */
	template <typename T>
	static void QuickSort(T *tab, int left, int right, bool descending = false);

	/* MergeSort                                                              */
    /* na podstwie  https://en.wikipedia.org/wiki/Merge_sort                  */
	template <typename T>
	static void MergeSort(T *tab, int left, int right, bool descending = false);

	/* HeapSort                                                               */
    /* na podstwie   http://informatyka.wroc.pl/node/433?page=0,4             */
	template <typename T>
	static void HeapSort(T *tab, int size, bool descending = false);

	/* IntrospectiveSort                                                      */
    /* na podstwie   https://pl.wikipedia.org/wiki/Sortowanie_introspektywne  */
	template <typename T>
	static void IntroSort(T *tab, int left, int right, int maxDepth, bool descending = false);
};

int Sorts::parentId(int i)
{
	return i / 2;
}

int Sorts::leftChildId(int i)
{
	return 2*i;
}

int Sorts::rightChildId(int i)
{
	return 2*i + 1;
}

template <typename T>
int Sorts::QuickSort_Split(T *tab, int left, int right, bool descending)
{
	int refIndex = (left + right) / 2;
	T pivot = tab[refIndex];

	int l = left, r = right - 1;

	swap(tab[refIndex], tab[right]);

	while (l <= r)
	{
		if (!descending)
		{
			while (tab[l] < pivot) l++;
			while (tab[r] > pivot) r--;
		}
		if (descending) {
			while (tab[l] > pivot) l++;
			while (tab[r] < pivot) r--;
		}

		if (l <= r)
		{
			swap(tab[l], tab[r]);
			l++;
			r--;
		}
	}
	swap(tab[l], tab[right]);

	return l;
}

template <typename T>
void Sorts::Merge(T *tab, int left, int middle, int right, bool descending)
{
	//auto tab_pom = std::make_unique<T[]>(right - left + 1);
	T *tab_pom = new int[right -left + 1];
	
	int i = left, j = middle + 1, k = 0;                      // zmienne pomocnicze

	while (i <= middle && j <= right)
	{
		if (descending ? tab[j] > tab[i] : tab[j] < tab[i])
		{
			tab_pom[k] = tab[j];
			j++;
		}
		else
		{
			tab_pom[k] = tab[i];
			i++;
		}
		k++;
	}

	if (i <= middle)
	{
		while (i <= middle)
		{
			tab_pom[k] = tab[i];
			i++;
			k++;
		}
	}
	else
	{
		while (j <= right)
		{
			tab_pom[k] = tab[j];
			j++;
			k++;
		}
	}

	for (i = 0; i <= right - left; i++)
		tab[left + i] = tab_pom[i];
	
	delete[] tab_pom;
}

template <typename T>
void Sorts::KopcujMax(T *tab, int i, int size)
{
	int largest;
	int lewy = leftChildId(i);
	int prawy = rightChildId(i);

	if (lewy <= size && tab[lewy] > tab[i])
	{
		largest = lewy;
	}
	else
	{
		largest = i;
	}

	if (prawy <= size && tab[prawy] > tab[largest])
	{
		largest = prawy;
	}

	if (largest != i)
	{
		swap(tab[i], tab[largest]);
		KopcujMax<T>(tab, largest, size);
	}
}

template <typename T>
void Sorts::KopcujMin(T *tab, int i, int size)
{
	int smallest;
	int lewy = leftChildId(i);
	int prawy = rightChildId(i);

	if (lewy <= size && tab[lewy] < tab[i])
	{
		smallest = lewy;
	}
	else
	{
		smallest = i;
	}

	if (prawy <= size && tab[prawy] < tab[smallest])
	{
		smallest = prawy;
	}

	if (smallest != i)
	{
		swap(tab[i], tab[smallest]);
		KopcujMin<T>(tab, smallest, size);
	}
}

template <typename T>
void Sorts::BudujKopiec(T *tab, int size, bool descending)
{
	for (int i = size / 2; i >= 1; i--)
	{
		descending? KopcujMin<T>(tab, i, size):KopcujMax<T>(tab, i, size);
	}
}

template <typename T>
void Sorts::HeapSort(T *tab, int size, bool descending)
{
	BudujKopiec<T>(tab, size, descending);

	for (int i = size ; i >= 2; i--)
	{
		swap(tab[i], tab[1]);
		descending ? KopcujMin<T>(tab, 1, i - 1) : KopcujMax<T>(tab, 1, i-1);
	}
}

template <typename T>
void Sorts::QuickSort(T *tab, int left, int right, bool descending)
{
	if (left < right)
	{
		int l = QuickSort_Split<T>(tab, left, right, descending);
		if (left < l - 1) QuickSort<T>(tab, left, l - 1, descending);
		if (l + 1 < right) QuickSort<T>(tab, l + 1, right, descending);
	}
}

template <typename T>
void Sorts::MergeSort(T *tab, int left, int right, bool descending)
{
	int middle;
	if (left != right)
	{
		middle = (left + right) / 2;
		MergeSort<T>(tab, left, middle, descending);
		MergeSort<T>(tab, middle + 1, right, descending);
		Merge<T>(tab, left, middle, right, descending);
	}
}

template <typename T>
void Sorts::IntroSort(T *tab, int left, int right, int maxDepth, bool descending) {
	if (left < right) {
		if (maxDepth == 0) {
			HeapSort<T>(tab + left - 1, (right - left) + 1, descending);
			return;
		}
		int n = QuickSort_Split<T>(tab, left, right, false);
		if (left < n - 1) IntroSort<T>(tab, left, n - 1, maxDepth - 1, descending);
		if (n + 1 < right) IntroSort<T>(tab, n + 1, right, maxDepth - 1, descending);
	}
}
#endif
