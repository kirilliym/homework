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
	if (i->next == j)
	{
		i->next = j->next;
		if (i->next) i->next->prev = i;
		i->prev = j;
		j->next = i;
		j->prev = p->prev;
		if (j->prev) j->prev->next = j;
	}
	else
	{
		i->next = j->next;
		if (i->next) i->next->prev = i;
		i->prev = j->prev;
		if (i->prev) i->prev->next = i;
		j->next = p->next;
		if (j->next) j->next->prev = j;
		j->prev = p->prev;
		if (j->prev) j->prev->next = j;
	}
}



void ListPrint(list* h)
{
	list* i = h;
	while (i)
	{
		cout << i->val << ' ';
		i = i->next;
	}
	cout << endl;
}



void QuickSort(list* h, list* t)
{
	if (t == h) return;

	int mn = 1e9, mx = -1;
	list* i = h, * j = t;
	while (i != t)
	{
		mn = min(i->val, mn);
		mx = max(i->val, mx);
		i = i->next;
	}
	mn = min(i->val, mn);
	mx = max(i->val, mx);
	int mid = (mx + mn) / 2;
	i = h;
	while (i != j)
	{
		while (i->val < mid && i != j) i = i->next;
		while (j->val > mid && i != j) j = j->prev;
		if (i != j)
		{
			if (h == i && t == j) swap(h, t);
			else if (h == i) h = j;
			else if (t == j) t = i;
				Swap(i, j);
				swap(i, j);
				i = i->next;
		}
	}
	if (i == h)
	{
		QuickSort(i->next, t);
	}
	else if (j == t)
	{
		QuickSort(h, j->prev);
	}
	else
	{
		QuickSort(h, i->prev);
		QuickSort(i, t);
	}
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

	list* r = hg;
	while (r)
	{
		hg = r;
		r = r->prev;
	}

	cout << "Result: ";
	ListPrint(hg);
}