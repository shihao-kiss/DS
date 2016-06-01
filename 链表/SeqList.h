#pragma once
#include <assert.h>

typedef int DataType;

class SeqList
{
public:
	SeqList()
		:_array(NULL)
		,_size(0)
		,_capacity(0)
	{
		cout<<"SeqList()"<<endl;	
	}

	SeqList(DataType* array, size_t size)
		:_array(new DataType[size])
		,_size(size)
		,_capacity(size)
	{
		cout<<"SeqList()"<<endl;	
		memcpy(_array, array, sizeof(DataType)*size);
	}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL; //?

			_size = 0;
			_capacity = 0;
		}
		cout<<"~SeqList()"<<endl;	
	}

	//SeqList(const SeqList& s)
	//{
	//	_array = new DataType[s._size];
	//	memcpy(_array, s._array, sizeof(DataType)*s._size);
	//	_size = s._size;
	//	_capacity = s._size;
	//}

	SeqList(const SeqList& s)
		:_array(NULL)
		,_size(0)
		,_capacity(0)
	{
		SeqList tmp(s._array, s._size);
		tmp.Swap(*this);
	}

	//SeqList& operator=(const SeqList& s)
	//{
	//	if (this != &s)
	//	{
	//		delete[] _array;

	//		_array = new DataType[s._size];
	//		memcpy(_array, s._array, sizeof(DataType)*s._size);
	//		_size = s._size;
	//		_capacity = s._size;
	//	}

	//	return  *this;
	//}

	SeqList& operator=(SeqList s)
	{
		s.Swap(*this);

		return *this;
	}

public:
	void Print()
	{
		for (int i = 0; i < _size; ++i)
		{
			cout<<_array[i]<<" ";
		}

		cout<<endl;
	}
	void PushBack(const DataType& x)
	{
		_CheckCapacity(_size+1);

		_array[_size++] = x;
	}

	void PopBack();
	//void PushFront(const DataType& x);
	//void PopFront();

	void Insert(size_t pos, const DataType& x);
	int Find(const DataType& x);
	void Erase(size_t pos);

	DataType& operator[](size_t index)
	{
		assert(_array);
		assert(index < _size);

		return _array[index];
	}

	size_t Size()
	{
		return _size;
	}

	size_t Capacity()
	{
		return _capacity;
	}

	void Reserve(size_t size) // ->保留空间，增容到size
	{
		_CheckCapacity(size);
	}

	void Clear()	// -> 不释放空间
	{
		_size = 0;
	}

	void Swap(SeqList& s)
	{
		std::swap(_array, s._array);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

	// 怎么样是释放空间??

private:
	void _CheckCapacity(size_t size)
	{
		if (size > _capacity)
		{
			_capacity = size > 2*_capacity ? size:2*_capacity;

			DataType* tmp = new DataType[_capacity];
			memcpy(tmp, _array, sizeof(DataType)*_size);
			delete[] _array;

			_array = tmp;
		}
	}

private:
	DataType* _array;
	size_t _size;
	size_t _capacity;
};



void Test1()
{
	int array[5] = {0, 1, 2, 3, 4};
	SeqList s1(array, 5);
	s1.Print();

	s1.PushBack(5);
	s1.PushBack(6);
	s1.Print();

	s1.Clear();
	s1.Print();
	cout<<s1.Capacity()<<endl;

	{
		SeqList tmp;
		tmp.Swap(s1);
	}

	cout<<s1.Capacity()<<endl;

	//SeqList s2(s1);
}

void Test2()
{
	int array[5] = {0, 1, 2, 3, 4};
	SeqList s1(array, 5);
	s1.Print();

	SeqList s2(s1);
	s2.Print();

	SeqList s3;

	s3 = s1;
	s3.Print();
}

//#include <vector>
//
//void Test2()
//{
//	std::vector<int> v1;
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//
//	cout<<v1.capacity()<<endl;
//
//	v1.clear();
//	cout<<v1.capacity()<<endl;
//
//	{
//		vector<int> tmp;
//		tmp.swap(v1);
//	}
//
//	cout<<v1.capacity()<<endl;
//}

