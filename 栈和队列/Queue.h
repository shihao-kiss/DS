#pragma once

template<class T>
struct QueueNode
{
	T _data;
	QueueNode<T>* _next;

	QueueNode(const T& x)
		:_data(x)
		,_next(NULL)
	{}
};

template<class T>
class Queue
{
public:	
	Queue()
		:_head(NULL)
		,_tail(NULL)
	{}

	~Queue()
	{}

public:
	void Push(const T& x)
	{
		if (_head == NULL)
		{
			_tail = _head = new QueueNode<T>(x);
		}
		else
		{
			_tail->_next = new QueueNode<T>(x);
			_tail = _tail->_next;
		}
	}

	void Pop()
	{
		assert(_head);
		if (_head == _tail)
		{
			delete _head;
			_tail = _head = NULL;
			return;
		}

		QueueNode<T>* del = _head;
		_head = _head->_next;
		delete del;
	}

	size_t Size();

	bool Empty()
	{
		return _head == NULL;
	}

	T& Fornt()
	{
		assert(_head);

		return _head->_data;
	}

	T& Back()
	{
		assert(_tail);

		return _tail->_data;
	}

protected:
	QueueNode<T>* _head;
	QueueNode<T>* _tail;
};

void Test2()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);

	while (!q.Empty())
	{
		cout<<q.Fornt()<<" ";
		q.Pop();
	}
}
