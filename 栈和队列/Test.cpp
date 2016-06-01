#include <iostream>
#include <assert.h>
using namespace std;

#include "Stack.h"
#include "TypeTraits.h"
#include "Queue.h"

enum Type
{
	OP_NUM,
	OP_SYMBOL
};

enum OP_SMB
{
	ADD,
	SUB,
	MUL,
	DIV,
};

struct Cell
{
	Type _type;
	int _value;
};

Cell RNPArray[11] = 
{
	{OP_NUM, 12},
	{OP_NUM, 3},
	{OP_NUM, 4},
	{OP_SYMBOL, ADD},
	{OP_SYMBOL, MUL},
	{OP_NUM, 6},
	{OP_SYMBOL, SUB},
	{OP_NUM, 8},
	{OP_NUM, 2},
	{OP_SYMBOL, DIV},
	{OP_SYMBOL, ADD},
};

int CountRNP(Cell* a, size_t size)
{
	stack<int> s;
	for (int i = 0; i < size; ++i)
	{
		if (a[i]._type == OP_NUM)
		{
			s.push(a[i]._value);
		}
		else if(a[i]._type == OP_SYMBOL)
		{
			int left = s.top();
			s.pop();
			int right = s.top();
			s.pop();

			switch(a[i]._value)
			{
			case ADD:
				s.push(left + right);
			case SUB:
				s.push(left - right);
			case MUL:
				s.push(left * right);
			case DIV:
				s.push(left / right);
			}
		}
	}
}

int main()
{
	//Test2();

	return 0;
}