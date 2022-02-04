#include<stdio.h>
#include<vector>
#define MaxNum 50
using namespace std;
bool topologicalsort(int adj[MaxNum][MaxNum], int n,vector<vector<int>>pre)
{
	int top = -1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj[i][j] = 0;
	int* count = new int[n];
	for (int j = 0; j < n; j++)
		count[j] = 0;
	while(!pre.empty())
	{
		vector<int> temp = pre.back();
		adj[temp[1]][temp[0]] = 1;
		count[temp[0]]++;
		pre.pop_back();
	}
	for(int i=0;i<n;i++)
		if (count[i] == 0)
		{
			count[i] = top;
			top = i;
		}
	for (int i = 0; i < n; i++)
	{
		if (top == -1)
			return false;
		else
		{
			int j = top;
			top = count[top];
			for (int k = 0; k < n; k++)
			{
				if (adj[j][k] == 1)
				{
					adj[j][k] = 0;
					if (--count[k] == 0)
					{
						count[k] = top;
						top = k;
					}
				}
			}
		}
	}
	return true;
}
int main()
{
	vector<vector<int>>prerequisites = { {1, 0},{0,1} };
	int numCourses = 2;
	int adj[MaxNum][MaxNum];
	if (topologicalsort(adj, numCourses, prerequisites))
		printf("true\n");
	else
		printf("false\n");
	return 0;
}