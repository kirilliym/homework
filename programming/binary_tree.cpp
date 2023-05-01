#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <deque>
#include <stack>

using namespace std;

vector<int> t;

struct tree
{
	int inf;
	tree* r;
	tree* l;
	tree* p;
};


tree* node(int x)
{
	tree* n = new tree;
	n->inf = x;
	n->r = n->l = n->p = nullptr;
	return n;
}

void insert(tree*& tr, int x)
{
	tree* n = node(x);
	if (!tr)
	{
		tr = n;
	}
	else
	{
		tree* y = tr;
		while (y)
		{
			if (n->inf > y->inf)
			{
				if (y->r)
				{
					y = y->r;
				}
				else
				{
					n->p = y;
					y->r = n;
					break;
				}
			}
			else if (n->inf < y->inf)
			{
				if (y->l)
				{
					y = y->l;
				}
				else
				{
					n->p = y;
					y->l = n;
					break;
				}
			}
			else break;
		}
	}
}

void preorder(tree* tr)
{
	if (tr)									//если существует узел, то спускается дальше
	{
		t.push_back(tr->inf);
		preorder(tr->l);
		preorder(tr->r);
	}
}

tree* Min(tree* tr)
{
	if (!tr->l) return tr;					//по левой вветке до конца
	else return Min(tr->l);
}

tree* Max(tree* tr)
{
	if (!tr->r) return tr;					//по правой ветке до конца
	else return Max(tr->r);
}

tree* find(tree* tr, int x)
{
	if (!tr || x == tr->inf) return tr;		//не нашел или нашел - воврат
	if (x < tr->inf) return find(tr->l, x);	//иначе решает куда спускаться
	else return find(tr->r, x);
}


tree* next(tree* tr, int x)
{
	tree* n = find(tr, x);
	if (n->r) return Min(n->r);				//если есть правый ребенок - минимум по правой ветке
	tree* y = n->p;
	while (y && n == y->r)					//пока не корень или правый ребенок
	{
		n = y;
		y = y->p;
	}
	return y;
}

tree* prev(tree* tr, int x)
{
	tree* n = find(tr, x);

	if (n->l) return Max(n->l);
	tree* y = n->p;
	while (y && n == y->l)
	{
		n = y;
		y = y->p;
	}
	return y;
}

void erase(tree*& tr, int x)
{
	tree* v = find(tr, x);
	if (!v) return;
	tree* p = v->p;
	if (!p && !v->l && !v->r) tr = nullptr;
	else if (!v->l && !v->r)				//no children
	{
		if (v == p->l) p->l = nullptr;
		if (v == p->r) p->r = nullptr;
		delete v;
	}
	else if (!v->l || !v->r)				//1 child
	{
		if (!p)								//koren
		{
			if (!v->l) tr = v->r;
			else tr = v->l;
			tr->p = nullptr;
		}
		else								//ne koren
		{
			if (!v->l)						//have right child
			{
				if (p->l == v)
				{
					p->l = v->r;
					v->r->p = p;
				}
				else
				{
					p->r = v->r;
					v->r->p = p;
				}
			}
			else							//have left child
			{
				if (p->l == v)
				{
					p->l = v->l;
					v->l->p = p;
				}
				else
				{
					p->r = v->l;
					v->l->p = p;
				}
			}
		}
		delete v;
	}
	else
	{
		tree* succ = next(tr, v->inf);
		v->inf = succ->inf;
		if (succ->p->l == succ)
		{
			succ->p->l = succ->r;
			if (succ->r) succ->r->p = succ->p;
		}
		else
		{
			succ->p->r = succ->r;
			if (succ->r) succ->r->p = succ->p;
		}
		delete succ;
	}
}


void task1()
{
	cout << "n = ";
	int n; cin >> n;
	tree* tr = nullptr;
	cout << "tree = ";
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		insert(tr, x);
	}
	t.clear();
	preorder(tr);
	for (int i = 0; i < t.size(); i++) if (t[i] % 2) erase(tr, t[i]);
	t.clear();
	preorder(tr);
	cout << "res = ";
	for (int i = 0; i < t.size(); i++) cout << t[i] << ' ';
	cout << endl;
}




void FindPath(tree* tr, int x)
{
	t.push_back(tr->inf);
	if (tr->inf == x) return;
	if (x > tr->inf) FindPath(tr->r, x);
	else FindPath(tr->l, x);
}


void task2()
{
	cout << "n = ";
	int n; cin >> n;
	tree* tr = nullptr;
	cout << "tree = ";
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		insert(tr, x);
	}
	t.clear();
	cout << "x = ";
	int x; cin >> x;
	if (find(tr, x))
	{
		FindPath(tr, x);
		cout << "path = ";
		for (int i = 0; i < t.size(); i++) cout << t[i] << ' ';
		cout << endl;
	}
	else cout << "no such element" << endl;
}


int main()
{
	cout << "task = ";
	int task; cin >> task;
	switch (task)
	{
	case 1: 
	{
		task1();
		break;
	}
	case 2:
	{
		task2();
		break;
	}
	default:
		break;
	}
}
