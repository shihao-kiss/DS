#pragma once

typedef int DataType;
struct SlistNode
{
//	friend class Slist;
//public:
	SlistNode(const DataType& x)
		:_data(x)
		,_next(NULL)
	{}

	//operator<<

	DataType _data;
	SlistNode* _next;
};

class Slist
{
public:
	Slist()
		:_head(NULL)
		,_tail(NULL)
	{}
	~Slist()
	{
		Clear();
	}

	//Slist(const Slist& s)
	//	:_head(NULL)
	//	,_tail(NULL)
	//{
	//	SlistNode* begin = s._head;
	//	while (begin)
	//	{
	//		if (_head == NULL)
	//		{
	//			_head = new SlistNode(begin->_data);
	//			_tail = _head;
	//		}
	//		else
	//		{
	//			_tail->_next = new SlistNode(begin->_data);
	//			_tail = _tail->_next;
	//		}

	//		begin = begin->_next;
	//	}
	//}

	Slist(const Slist& s)
		:_head(NULL)
		,_tail(NULL)
	{
		SlistNode* begin = s._head;
		while (begin)
		{
			PushBack(begin->_data);

			begin = begin->_next;
		}
	}

	/*Slist& operator=(const Slist& s)
	{
		if(this != &s)
		{
			Clear();
			SlistNode* begin = s._head;
			while (begin)
			{
				PushBack(begin->_data);

				begin = begin->_next;
			}
		}

		return *this;
	}*/

	//Slist& operator=(const Slist& s)
	//{
	//	if(this != &s)
	//	{
	//		Slist tmp(s);
	//		tmp.Swap(*this);
	//	}

	//	return *this;
	//}

	Slist& operator=(Slist s)
	{
		this->Swap(s);

		return *this;
	}
public:
	void Print()
	{
		SlistNode* begin = _head;
		while (begin)
		{
			cout<<begin->_data<<"->";
			begin = begin->_next;
		}

		cout<<"NULL"<<endl;
	}

	void PushBack(const DataType& x)
	{
		if (_head == NULL)
		{
			_head = new SlistNode(x);
			_tail = _head;
		}
		else
		{
			_tail->_next = new SlistNode(x);
			_tail = _tail->_next;
		}
	}

	void PopBack()
	{
		// 1.空
		// 2.一个节点
		// 3.一个以上节点
		if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			SlistNode* tailPrev = _head;
			while (tailPrev->_next != _tail)
			{
				tailPrev = tailPrev->_next;
			}

			tailPrev->_next = NULL;
			delete _tail;
			_tail = tailPrev;
		}
	}

	SlistNode* Find(const DataType& x)
	{
		SlistNode* begin = _head;
		while (begin)
		{
			if (begin->_data == x)
			{
				return begin;
			}

			begin = begin->_next;
		}

		return NULL;
	}

	void Insert(SlistNode* pos, const DataType& x);
	void Erase(SlistNode* pos);

	void Swap(Slist& s)
	{
		swap(s._head, _head);
		swap(s._tail, _tail);
	}

	void Clear()
	{
		SlistNode* begin = _head;
		while (begin)
		{
			SlistNode* del = begin;
			begin = begin->_next;
			delete del;
		}

		_head = _tail = NULL;
	}

private:
	SlistNode* _head;
	SlistNode* _tail;
};

void Test1()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.Print();

	//Slist s2(s1);

	SlistNode* ret = s1.Find(3);
	cout<<ret->_data<<endl;

	s1.PopBack();
	s1.PopBack();
	s1.PopBack(); // PopBack()->3

	s1.PopBack(); // PopBack()->2
	s1.PopBack(); // PopBack()->1
	s1.Print();
}

void Test2()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.Print();

	Slist s2(s1);
	s2.Print();

	Slist s3;
	s3= s1;
	s3.Print();
}