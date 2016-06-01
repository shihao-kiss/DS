#pragma once

#include <memory.h>
#include<assert.h>

#define  MAX_SIZE 100
typedef int DataType;
typedef struct SeqList
{
	DataType array[MAX_SIZE];	// 数据段
	size_t size;				// 数据个数
}SeqList;

void InitSeqList(SeqList* pSeq)
{
	memset(pSeq->array, 0, sizeof(DataType)*MAX_SIZE);
	pSeq->size = 0;
}

void PrintSeqList(SeqList* pSeq)
{
	size_t i = 0;
	assert(pSeq);

	for (i = 0; i < pSeq->size; ++i)
	{
		printf("%d ", pSeq->array[i]);
	}

	printf("\n");
}

void PushBack(SeqList* pSeq, DataType x)
{
	assert(pSeq);

	if (pSeq->size >= MAX_SIZE)
	{
		printf("SeqList is Full\n");
		return;
	}

	pSeq->array[pSeq->size++] = x;
}

void PopBack(SeqList* pSeq)
{
	assert(pSeq);

	if (pSeq->size == 0)
	{
		printf("SeqList is Empty\n");
		return;
	}

	--pSeq->size;
	//pSeq->array[--pSeq->size] = 0;
}

void PushFront(SeqList* pSeq, DataType x)
{
	int begin =  pSeq->size - 1;
	assert(pSeq);

	if (pSeq->size >= MAX_SIZE)
	{
		printf("SeqList is Full\n");
		return;
	}

	for (; begin >= 0; --begin)
	{
		pSeq->array[begin + 1] = pSeq->array[begin];
	}

	pSeq->array[0] = x;

	++pSeq->size;
}

void PopFront(SeqList* pSeq)
{
	int i = 1;
	assert(pSeq);

	if (pSeq->size == 0)
	{
		printf("SeqList is Empty\n");
		return;
	}

	for (; i < pSeq->size; ++i)
	{
		pSeq->array[i -1] = pSeq->array[i];
	}

	--pSeq->size;
}

void Insert(SeqList* pSeq, size_t pos, DataType x)
{
	int begin =  pSeq->size - 1;
	assert(pSeq);

	if (pSeq->size >= MAX_SIZE)
	{
		printf("SeqList is Full\n");
		return;
	}

	if (pos > pSeq->size)
	{
		printf("Pos is Over Cross\n");
	}

	for (; begin >= pos; --begin)
	{
		pSeq->array[begin + 1] = pSeq->array[begin];
	}

	pSeq->array[pos] = x;

	++pSeq->size;
}

int Find(SeqList* s, DataType x)
{
	int i = 0;
	assert(s);

	for (; i < s->size; ++i)
	{
		if (s->array[i] == x)
		{
			return i;
		}
	}

	return  -1;
}

// 删除pos位置的数据
void Erase(SeqList* s, size_t pos)
{
	int i = pos;
	assert(s);
	assert(pos < s->size);

	for (; i < s->size - 1; ++i)
	{
		s->array[i] = s->array[i + 1];
	}

	s->size--;
}

// 删除找到的第一个x
void Remove(SeqList* s, DataType x)
{
	//int ret;
	//assert(s);

	//ret = Find(s, x);
	//if (ret != -1)
	//{
	//	Erase(s, ret);
	//}

	int i = 0;
	assert(s);


	for (; i < s->size; ++i)
	{
		if (s->array[i] == x)
		{
			int j = i;
			for (; j < s->size - 1; ++j)
			{
				s->array[j] = s->array[j + 1];
			}

			break;
		}
	}
}

// 删除所有的x
//void RemoveAll(SeqList* s, DataType x)
//{
//	//int ret;
//	//assert(s);
//
//	//ret = Find(s, x);
//	//while(ret != -1)
//	//{
//	//	Erase(s, ret);
//	//	ret = Find(s, x);
//	//}
//
//	int count = 0;
//	int i = 0;
//	assert(s);
//
//	for (; i < s->size; ++i)
//	{
//		if (s->array[i] == x)
//		{
//			int j = i;
//			for (; j < s->size - 1; ++j)
//			{
//				s->array[j] = s->array[j + 1];
//			}
//			++count;
//			--i;
//		}
//	}
//}

void RemoveAll(SeqList* pSeq, DataType x)
{
	int count = 0;
	int firstIndex = 0, secondIndex = 0;
	assert(pSeq);

	while (secondIndex < pSeq->size)
	{
		if (pSeq->array[secondIndex] != x)
		{
			pSeq->array[firstIndex] = pSeq->array[secondIndex];
			++firstIndex;
		}
		else
		{
			++count;
		}

		++secondIndex;
	}

	pSeq->size -= count;
}

// 冒泡排序
void BubbleSort(SeqList* pSeq)
{
	int begin = 1;
	int end = pSeq->size;
	assert(pSeq);

	for(; end > 0; --end)
	{
		int exchange = 0;
		for (; begin < end; ++begin)
		{
			if (pSeq->array[begin - 1] > pSeq->array[begin])
			{
				DataType tmp = pSeq->array[begin - 1];
				pSeq->array[begin - 1] = pSeq->array[begin];
				pSeq->array[begin] = tmp;
				exchange = 1;
			}
		}

		if (exchange == 0)
		{
			return;
		}
	}
}

void SeclectSort(SeqList* pSeq)
{
	int begin = 0;
	int minIndex = 0;
	int maxIndex = 0;

	int curIndex = minIndex + 1;
	assert(pSeq);

	for (begin = 0; begin < pSeq->size - 1; ++begin)
	{
		DataType tmp;
		minIndex = begin;
		for (curIndex = begin + 1; curIndex < pSeq->size; ++curIndex)
		{
			if (pSeq->array[curIndex] < pSeq->array[minIndex])
			{
				minIndex = curIndex;
			}
		}
		tmp = pSeq->array[begin];
		pSeq->array[begin] = pSeq->array[minIndex];
		pSeq->array[minIndex] = tmp;
	}
}

void Swap(DataType* left, DataType* right)
{
	DataType tmp = *left;
	*left = *right;
	*right = tmp;
}

void SeclectSort_OP(SeqList* pSeq)
{
	int begin = 0, end = pSeq->size-1, cur = 0;
	int minIndex = 0;
	int maxIndex = 0;

	assert(pSeq);

	while(cur < end)
	{
		DataType max, min;
		for (begin = cur; begin <= end; ++begin)
		{
			if (pSeq->array[begin] < pSeq->array[cur])
			{
				Swap(pSeq->array + begin, pSeq->array + cur);
			}

			if (pSeq->array[begin] > pSeq->array[end])
			{
				Swap(pSeq->array + begin, pSeq->array + end);
			}
		}

		++cur;
		--end;
	}
}


int BinarySearch(SeqList* pSeq, DataType x)
{
	//[]
	//[)
	int left = 0;
	int right = pSeq->size;
	assert(pSeq);

	while (left < right)
	{
		// 1, 3
		//int mid = (left + right)/2;
		//int mid = left/2 + right/2;
		int mid = left + (right - left)/2;
		if (pSeq->array[mid] < x)
		{
			left = mid + 1;
		}
		else if (pSeq->array[mid] > x)
		{
			right = mid;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}

// 递归
//[0, size-1]
//[left, mid -1] | [mid+1, right]

int _BinarySearch_R(SeqList* pSeq, int left, int right, DataType x)
{
	//[)  0, size
	//[]  0, size -1
	assert(pSeq);
	if (left < right)
	{
		int mid = left + (right - left)/2;
		if (pSeq->array[mid] < x)
		{
			return _BinarySearch_R(pSeq, mid + 1, right, x);
		}
		else if(pSeq->array[mid] > x)
		{
			return _BinarySearch_R(pSeq, left, mid, x);
		}
		else
		{
			return mid;
		}
	}

	return -1;
}

int BinarySearch_R(SeqList* pSeq, DataType x)
{
	return _BinarySearch_R(pSeq, 0, pSeq->size, x);
}

