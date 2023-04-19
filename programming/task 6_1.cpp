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

void pop(list*& h, list*& t, list*& i)
{
	if (i == h && i == t)
	{
		h = nullptr; t = nullptr;
	}
	else if (i == h)
	{
		h = h->next;
		h->prev = nullptr;
	}
	else if (i == t)
	{
		t = t->prev;
		t->next = nullptr;
	}
	else
	{
		i->next->prev = i->prev;
		i->prev->next = i->next;
	}
	delete i;
}

void ListPrint(list*& h)
{
	list* i = h;
	while (i)
	{
		cout << i->val << ' ';
		i = i->next;
	}
}

int main()
{
	list *h = nullptr, *t = nullptr;
	cout << "n = ";
	int n; cin >> n;
	cout << "List: ";
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		push(h, t, x);
	}
	list* i = h;
	while (i)
	{
		if (i->val % 2)
		{
			pop(h, t, i);
			break;
		}
		i = i->next;
	}
	i = t;
	while (i)
	{
		if (i->val % 2)
		{
			pop(h, t, i);
			break;
		}
		i = i->prev;
	}
	cout << "Result: ";
	ListPrint(h);
}