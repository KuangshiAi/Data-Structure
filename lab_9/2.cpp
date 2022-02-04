#include<stdio.h>
#include<vector>
#include<algorithm>
#include"UFsets.h"
using namespace std;
int minCost(int N, vector<vector<int>>& connections)
{
	int ans = 0;
	int num = 0;//边的数目,到达N-1即完成
	auto cmp = [](vector<int>& a, vector<int>& b) {return a[2] < b[2]; };
	sort(connections.begin(), connections.end(), cmp);
	UFSets f(N + 1);
	for (int i = 0; i < connections.size(); i++)
	{
		int p = f.Find(connections[i][0]);
		int q = f.Find(connections[i][1]);
		if (p != q)
		{
			ans += connections[i][2];
			num++;
			f.WeightedUnion(connections[i][0], connections[i][1]);
		}
	}
	if (num == N - 1)
		return ans;
	return -1;
}
int main()
{
	vector<vector<int>> connections = { {1, 2, 5} ,{1, 3, 6},{2, 3, 1} };
	int N = 3;
	printf("最小成本是%d",minCost(N, connections));
	return 0;
}