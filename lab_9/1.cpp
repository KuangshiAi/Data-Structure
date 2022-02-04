#include"UFsets.h"
#include<stdio.h>
#include<vector>
using namespace std;
#include<algorithm>
void FindPond(vector<vector<int>>map)
{
	int m = map.size();
	int n = map[0].size();
	UFSets f(m * n);
	vector<vector<int>> move = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	int i,j,k;
	for (i = 0; i < m ; i++)
		for(j=0;j<n;j++)
	{
			if (map[i][j] == 0)
			{
				k = 0;
				while (k < 8)
				{
					int ni = i + move[k][0];
					int nj = j + move[k][1];
					if (ni < 0 || ni >= m || nj < 0 || nj >= n || map[ni][nj] > 0);
					else
					{
						if (f.Find(ni * n + nj) != f.Find(i * n + j))
						{
							f.Union(ni * n + nj, i * n + j);
						}
					}
					k++;
				}
			}
	}
	int *result=new int(m*n);
	for (i = 0, j = 0; i < m * n; i++)
	{
		if (f.parent[i] < 0&&map[i/n][i%n]==0)
			result[j++] = -f.parent[i];
	}
	for(i=0;i<j-1;i++)
		for (int k = 0; k < j - 1 - i; k++)
		{
			if (result[k] > result[k + 1])
			{
				int temp = result[k];
				result[k] = result[k + 1];
				result[k + 1] = temp;
			}
		}
	printf("[");
	for (i = 0; i < j; i++)
	{
		printf("%d ", result[i]);
	}
	printf("]");
}
int main()
{
	vector<vector<int>> map = {{ 0,2,1,0 }, { 0, 1, 0, 1 }, { 1, 1, 0, 1 }, { 0, 1, 0, 1 }};
	FindPond(map);
	return 0;
}
