#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>

using namespace std;

struct Elem
{
	Elem* link;
	int info;
};

void CreateCycle(Elem*& first, int N, int Low, int High, int k);
void Insert(Elem*& L, int value);
void Scanning(Elem* L, Elem* first, int x);
void Remove(Elem*& L);
void Print(Elem* L, Elem* first);

int main()
{
	srand((unsigned)time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Elem* L = NULL;

	int Low, High, N, x;
	cout << "Найменший елемент списку: "; cin >> Low;
	cout << "Найбільший елемент списку: "; cin >> High;
	cout << "Кількість елементів списку: "; cin >> N;
	cout << "Значення інформаційного поля: "; cin >> x;
	CreateCycle(L, N, Low, High, 0);
	Elem* first = L;
	cout << "Оригінальний список:" << endl;
	Print(L, first);
	cout << endl;
	cout << "Новий список:" << endl;
	Scanning(L, first, x);
	Print(L, first);
	cout << endl;

	system("pause");
	return 0;
}

void CreateCycle(Elem*& first, int N, int Low, int High, int k)
{
	if (k < N)
	{
		int value = Low + rand() % (High - Low + 1);
		Insert(first, value);
		CreateCycle(first, N, Low, High, k + 1);
	}
}

void Insert(Elem*& L, int value)
{
	Elem* tmp = new Elem;
	tmp->info = value;
	if (L != NULL)
	{
		Elem* T = L;
		while (T->link != L)
			T = T->link;
		T->link = tmp;
	}
	else
	{
		L = tmp;
	}
	tmp->link = L;
}

void Scanning(Elem* L, Elem* first, int x)
{
	if (L == NULL)
		return;
	else
	{
		if (L->link != first)
		{
			if (L->info == x)
			{
				Remove(L);
				Scanning(L, first, x);
			}
			else
				Scanning(L->link, first, x);
		}
	}
}

void Remove(Elem*& L)
{
	Elem* T = L->link;
	while (T->link != L->link)
		T = T->link;

	if (T != L->link)
	{
		Elem* tmp = L->link->link;
		delete L->link;
		L->link = tmp;
		T->link = L->link;
	}
	else
	{
		delete L->link;
		L->link = NULL;
	}
}

void Print(Elem* L, Elem* first)
{
	if (L == NULL)
		return;
	else
	{
		if (L->link != first)
		{
			cout << setw(4) << L->link->info;
			Print(L->link, first);
		}
	}
}
