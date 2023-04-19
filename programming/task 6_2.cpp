#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

struct list {
	int val;
	list* prev;
	list* next;
};

list* hg = nullptr, * tg = nullptr;

void push(list*& h, list*& t, int x)
{
	list* p = new list;
	p->val = x;
	p->next = nullptr;
	if (!h && !t)
	{
		p->prev = nullptr;
		h = p;
	}
	else
	{
		t->next = p;
		p->prev = t;
	}
	t = p;
}

void Swap(list*& i, list*& j)
{
	list* p = new list;
	p->next = i->next;
	p->prev = i->prev;
	i->next = j->next;
	i->prev = j->prev;
	j->next = p->next;
	j->prev = p->prev;
}

void QuickSort(list* h, list* t)
{
	if (t == h) return;
	int mn = 1e9, mx = -1;
	list* i = h, * j = t;
	while (i)
	{
		mn = min(i->val, mn);
		mx = max(i->val, mx);

		i = i->next;
	}
	int mid = (mx + mn) / 2;
	i = h;
	while (i != j)
	{
		while (i->val < mid && i != j) i = i->next;
		while (j->val > mid && i != j) j = j->prev;
		if (i != j)
		{
			Swap(i, j);
			swap(i, j);
		}
	}
	ListPrint(hg);
	QuickSort(h, j->prev);
	QuickSort(j, t);
}

void ListPrint(list*& h)
{
	list* i = h;
	while (i)
	{
		cout << i->val << ' ';
		i = i->next;
	}
	cout << endl;
}

int main()
{
	cout << "n = ";
	int n; cin >> n;
	cout << "List: ";
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		push(hg, tg, x);
	}
	QuickSort(hg, tg);
	cout << "Result: ";
	ListPrint(hg);
}