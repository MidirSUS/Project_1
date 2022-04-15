#include <iostream>
#include <set>
#include <conio.h>
#include <typeinfo>
#include <string>

using namespace std;

void Kruskal(int n, int** cost) 
{
	int a, b, v, u, i, j, num_edge = 1, min_, mincost = 0;
	int path_index = 0;
	set<int> Path; //В это множество будут записываться вершины, по которым составиться путь

	int* visited = new int[n];
	for (i = 0; i < n; i++)
		visited[i] = 0;

	cout << endl;
	cout << "Ребро | Вес" << endl;

	while (num_edge < n)
	{
		for (i = 0, min_ = 999; i < n; i++)
			for (j = 0; j < n; j++)
				if (cost[i][j] < min_)
				{
					min_ = cost[i][j];
					a = u = i;
					b = v = j;
					visited[a] = 1;
				}
		if ((visited[u] != 0 || visited[v] != 0) && (Path.find(u) == Path.end() || Path.find(v) == Path.end()))
		{
			Path.insert(b);
			path_index++;

			num_edge++;
			mincost += min_;
			visited[b] = 1;
			cout << a + 1 << " - " << b + 1 << " |  " << min_ << endl;
		}
		cost[a][b] = cost[b][a] = 999;
	}

	cout << "Минимальная стоимость:  " << mincost;
	delete[] visited;
	Path.clear();
}

void Prima(int n, int** cost)
{
	int a, b, u, v, i, j, num_edge = 1, min_, mincost = 0;
	int path_index = 0;
	int* path = new int[n]; //В этот массив будут записываться вершины, по которым составиться путь
	int* visited = new int[n];
	for (i = 0; i < n; i++)
		visited[i] = 0;

	visited[0] = 1;
	cout << endl;

	cout << "Ребро | Вес" << endl;

	while (num_edge < n)
	{
		for (i = 0, min_ = 999; i < n; i++)
			for (j = 0; j < n; j++)
				if (cost[i][j] < min_)
					if (visited[i] != 0)
					{
						min_ = cost[i][j];
						a = u = i;
						b = v = j;
					}
		if (visited[u] == 0 || visited[v] == 0)
		{
			path[path_index] = b;
			path_index++;

			num_edge++; 
			mincost += min_;
			visited[b] = 1;
			cout << a + 1 << " - " << b + 1 << " |  " << min_ << endl;
		}
		cost[a][b] = cost[b][a] = 999;
	}

	cout << "Минимальная стоимость:  " << mincost;
	delete[] visited;
	delete[] path;
}

int main()
{
	char ch = 0; bool correct = false, finish = false, cin_correct = false;
	setlocale(LC_ALL, "Russian");
	int n = 0; 
	cout << "Нахождение минимального остовного дерева" << endl << "алгоритмами Краскала и Прима." << endl;
	cout << "============================" << endl;
	while (!finish)
	{
		cout << "Введите количество вершин: ";
		/*Блок проверки ввода n:*/
		while (!cin_correct)
		{
			cin >> n;
			if (!cin)
			{
				cout << "Введено нецелочисленное значение, повторите ввод: " << endl;
				cin.clear();
				while (cin.get() != '\n');
			}
			else cin_correct = true;
		}
		int** cost = new int* [n + 1];
		for (int a = 0; a < n + 1; a++)
			cost[a] = new int[n + 1];

		cout << "Введите матрицу смежности:" << endl;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				cin >> cost[i][j];
				if (cost[i][j] == 0)
					cost[i][j] = 999; //999 - условное обозначение бесконечности. Должно быть больше чем значения веса каждого из ребер в графе
			}
		ch = 0;
		cout << "Выберите алогиртм: 'P' - Прима, 'K' - Краскала: ";
		cin >> ch;
		/*Блок проверки ввода ch:*/
		while (!correct)
		{
			if (ch == 'P' || ch == 'p')
			{
				Prima(n, cost);
				correct = true;
			}
			if (ch == 'K' || ch == 'k')
			{
				Kruskal(n, cost);
				correct = true;
			}
			if (ch != 'P' && ch != 'K' && ch != 'p' && ch != 'k')
			{
				cout << "Ошибка, повторите ввод: ";
				cin >> ch;
			}
		}
		cout << endl << endl;
		system("pause");
		system("cls");
		correct = false;
		cin_correct = false;
		delete[] cost;
		cout << "Обойти еще один граф? 'y' - Да, 'n' - Нет." << endl;
		cin >> ch;
		/*Блок проверки выбора: */
		while (!correct)
		{
			if (ch == 'Y' || ch == 'y')
			{
				finish = false;
				system("cls");
				break;
			}
			if (ch == 'N' || ch == 'n')
			{
				finish = true;
				system("cls");
				cout << "Всего доброго!" << endl;
				break;
			}
			if (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
			{
				cout << "Ошибка, повторите ввод: ";
				cin >> ch;
			}
		}
	}
	return 0;
}
	