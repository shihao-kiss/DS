#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<assert.h>
#include<windows.h>
using namespace std;

const int N = 100000;
const int K = 100;

// 创建红包数据
void CreateRedPacket(vector<int>& moneys)
{
	srand(time(0));
	moneys.reserve(N);
	for (int i = 0; i < N; ++i)
	{
		moneys.push_back(rand()%10000);
	}

	for(int j = N - K; j < N; ++j)
	{
		moneys[j] = rand() % N;
	}
}

void AdjustDown(int* a, size_t size, int root)
{
	int child = root*2+1;
	while (child < size)
	{
		if (child+1 <size && a[child+1] < a[child])
		{
			++child;
		}

		if (a[child] < a[root])
		{
			swap(a[child], a[root]);
			root = child;
			child = 2*root+1;
		}
		else
		{
			break;
		}
	}
}

void GetTopK(vector<int>& moneys)
{
	int arrays[K] = {};
	for (size_t i = 0; i < K; ++i)
	{
		arrays[i] = moneys[i];
	}

	// 建小堆
	for(int i = (K-2)/2; i >= 0; --i)
	{
		AdjustDown(arrays, K, i);
	}

	for (size_t i = K; i < N; ++i)
	{
		if (arrays[0] < moneys[i])
		{
			arrays[0] = moneys[i];
			AdjustDown(arrays, K, 0);
		}
	}

	for (int i = 0; i < K; ++i)
	{
		cout<<arrays[i]<<" ";
	}

	cout<<endl;
}

void TestTopK()
{
	vector<int> moneys;
	CreateRedPacket(moneys);
	GetTopK(moneys);
}