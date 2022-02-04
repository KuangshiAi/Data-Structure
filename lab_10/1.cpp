#include<stdio.h>
#include<vector>
#define EdgesMaxNum 40
using namespace std;
void initialize(int edges[EdgesMaxNum][EdgesMaxNum], int n, vector<vector<int>> time)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			edges[i][j] = 0;
	while (!time.empty())
	{
		vector<int>temp;
		temp = time.back();
		edges[temp[0]-1][temp[1]-1] = temp[2];
		time.pop_back();
	}
}
void shortestpath(int edges[EdgesMaxNum][EdgesMaxNum], int n, int k, int* dist, int* s)
{
	for (int i = 0; i < n; i++)
	{
		dist[i] = edges[k-1][i];
		s[i] = 0;
	}
	s[k-1] = 1;
	for (int i = 0; i < n - 1; i++)
	{
		int v = -1;
		int min = 60000;
		for (int j = 0; j < n; j++)
		{
			if (s[j] == 0)
			{
				if (dist[j] != 0 && dist[j] < min)
				{
					min = dist[j];
					v = j;
				}
			}
		}
		if (v == -1)
		{
			break;
		}
		s[v] = 1;
		for (int j = 0; j < n; j++)
		{
			int w = edges[v][j];
			if (s[j] == 0 && w != 0 && (dist[v] + w < dist[j]||dist[j]==0))
				dist[j] = dist[v] + w;
		}
		
	}
}
int finalresult(int n, int s[], int dist[])
{
	for (int i = 0; i < n; i++)
		if (s[i] == 0)
			return -1;
	int max = dist[0];
	for (int i = 0; i < n; i++)
	{
		if (dist[i] > max)
			max = dist[i];
	}
	return max;
}
int main()
{
	vector<vector<int>> time = { {2, 1, 1},{2, 3, 1},{3, 4, 1} };
	int n = 4;
	int k = 2;
	int edges[EdgesMaxNum][EdgesMaxNum];
	int* s = new int[n];
	int* dist = new int[n];
	initialize(edges, n, time);
	shortestpath(edges, n, k, dist, s);
	printf("%d\n",finalresult(n, s, dist) );
	return 0;
}