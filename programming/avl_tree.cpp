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

vector<int> a, ans;
int ind = 0, k = 0;
int level = -1;

struct tree
{
	int inf;
	tree* r;
	tree* l;
};


tree* node(int x)
{
	tree* n = new tree;
	n->inf = x;
	n->r = n->l = nullptr;
	return n;
}


void create(tree *&tr, int n)
{
	int x;
	if (n > 0)
	{
		x = a[ind++];
		tr = node(x);
		int nl = n / 2;
		int nr = n - nl - 1;
		create(tr->l, nl);
		create(tr->r, nr);
	}
}


void preorder(tree* tr, int lvl = 1)
{
	if (tr)
	{
		if (lvl == level) ans.push_back(tr->inf);
		if (!tr->l && !tr->r) k++;
		preorder(tr->l, lvl+1);
		preorder(tr->r, lvl+1);
	}
}


void task3()
{
	int n;
	cout << "n = ";
	cin >> n;
	a.resize(n);
	cout << "tree = ";
	for (int i = 0; i < n; i++) cin >> a[i];
	tree* tr = nullptr;
	create(tr, n);
	preorder(tr);
	cout << "leaves count = " << k << endl;
}

void task4()
{
	int n;
	cout << "n = ";
	cin >> n;
	a.resize(n);
	cout << "tree = ";
	for (int i = 0; i < n; i++) cin >> a[i];
	tree* tr = nullptr;
	create(tr, n);
	cout << "k = ";
	cin >> level;
	ans.clear();
	preorder(tr);
	for (int i = 0; i < ans.size(); i++) cout << ans[i] << ' ';
	cout << endl;
}


int main()
{
	cout << "task = ";
	int task; cin >> task;
	switch (task)
	{
	case 3: 
	{
		task3();
		break;
	}
	case 4:
	{
		task4();
		break;
	}
	default:
		break;
	}
}
