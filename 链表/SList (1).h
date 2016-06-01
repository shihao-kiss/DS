#pragma once
#include <assert.h>
#include <malloc.h>

typedef int DataType ;

typedef struct ListNode
{
	DataType   _data ;			// 数据
	struct ListNode* _next;     // 指向下一个节点的指针
}ListNode;

void InitList(ListNode** pHead)
{
	*pHead = NULL;
}

void DestoryList(ListNode*& pHead)
{
	ListNode* cur = pHead;
	while (cur)
	{
		ListNode* tmp = cur;
		cur = cur->_next;
		free(tmp);
	}

	pHead = NULL;
}

ListNode* BuyNode(DataType x)
{
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	assert(tmp);
	tmp->_data = x;
	tmp->_next = NULL;

	return tmp;
}

//void PushBack(ListNode** ppHead, DataType x)
//{
//	assert(ppHead);
//
//	// 1.空链表
//	// 2.非空
//	if (*ppHead == NULL)
//	{
//		*ppHead = BuyNode(x);
//	}
//	else
//	{
//		ListNode* tail = *ppHead;
//		while (tail->_next != NULL)
//		{
//			tail = tail->_next;
//		}
//		
//		tail->_next = BuyNode(x);
//		//ListNode* tmp = BuyNode(x);
//		//tmp = tail->_next;
//	}
//}

void PrintList(ListNode* pHead)
{
	ListNode* cur = pHead;
	while (cur != NULL)
	{
		printf("%d->", cur->_data);
		cur = cur->_next;
	}

	printf("NULL\n");
}

void PushBack(ListNode*& pHead, DataType x)
{
	// 1.空链表
	// 2.非空
	if (pHead == NULL)
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode* tail = pHead;
		while (tail->_next != NULL)
		{
			tail = tail->_next;
		}

		tail->_next = BuyNode(x);
		//ListNode* tmp = BuyNode(x);
		//tmp = tail->_next;
	}
}

void PushFront(ListNode*& pHead, DataType x)
{
	// 1.为空
	// 2.非空
	if(pHead == NULL)
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode* tmp = BuyNode(x);
		tmp->_next = pHead;

		pHead = tmp;
	}
}

void PopBack(ListNode*& pHead)
{
	// 1.空
	// 2.一个节点
	// 3.多个节点
	if(pHead == NULL)
	{
		printf("List is empty\n");
		return;
	}
	else if (pHead->_next == NULL)
	{
		free(pHead);
		pHead = NULL;
	}
	else
	{
		ListNode* prevTail = NULL, *tail = pHead;
		while(tail->_next != NULL)
		{
			prevTail = tail;
			tail = tail->_next;
		}

		prevTail->_next = NULL;
		free(tail);
	}
}

void PopFront(ListNode*& pHead)
{
	if (pHead == NULL)
	{
		printf("List is Empty\n");
		return;
	}
	else
	{
		ListNode* del = pHead;
		pHead = pHead->_next;

		free(del);
	}
}

ListNode* Find(ListNode* pHead, DataType x)
{
	ListNode* cur = pHead;
	while (cur)
	{
		if (cur->_data == x)
		{
			return cur;
		}

		cur = cur->_next;
	}

	return NULL;
}

void Insert(ListNode* pos, DataType x)
{
	assert(pos);
	/*ListNode* tmp = BuyNode(x);
	tmp->_next = pos->_next;
	pos->_next = tmp;*/

	ListNode* next = pos->_next;
	ListNode* tmp = BuyNode(x);
	pos->_next = tmp;
	tmp->_next = next;
}

void Erase(ListNode*& pHead, ListNode* pos)
{
	assert(pos);

	if (pos == pHead)
	{
		pHead = pHead->_next;
		free(pos);
	}
	else
	{
		ListNode* cur = pHead;
		while(cur)
		{
			if(cur->_next == pos)
			{
				cur->_next = pos->_next;
				free(pos);
				break;
			}

			cur = cur->_next;
		}
	}
}

void DelNonTailNode(ListNode* pos)
{
	assert(pos && pos->_next);

	pos->_data = pos->_next->_data;
	ListNode* next = pos->_next->_next;
	free(pos->_next);
	pos->_next = next;
}

void Remove(ListNode*& pHead, DataType x)
{
	ListNode* ret = Find(pHead, x);
	if (ret)
	{
		Erase(pHead, ret);
	}
}

ListNode* Reverse(ListNode* pHead)
{
	ListNode* newHead = NULL;
	ListNode* cur = pHead;

	while (cur)
	{
		ListNode* tmp = cur;
		cur = cur->_next;

		tmp->_next = newHead;
		newHead = tmp;
	}

	return newHead;
}

void PrintTailToHead(ListNode* pHead)
{
	if (pHead)
	{
		PrintTailToHead(pHead->_next);
		
		printf("%d ", pHead->_data);
	}
}

void InsertFrontNode(ListNode* pos, DataType x)
{
	assert(pos);

	//ListNode* tmp = BuyNode(x);
	//tmp->_next = pos->_next;
	//pos->_next = tmp;

	//DataType tmpData = tmp->_data;
	//tmp->_data = pos->_data;
	//pos->_data = tmpData;


	ListNode* tmp = BuyNode(pos->_data);
	tmp->_next = pos->_next;
	pos->_next = tmp;

	pos->_data = x;
}

ListNode* FindMid(ListNode* pHead)
{
	ListNode* slow = pHead, *fast = pHead;

	// 
	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
	}

	return slow;
}

