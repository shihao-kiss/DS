//#pragma once
//
//enum Status
//{
//	EXITS,
//	DELETE,
//	EMPTY,
//};
//
//static size_t BKDRHash(const char * str)
//{
//	unsigned int seed = 131; // 31 131 1313 13131 131313
//	unsigned int hash = 0;
//	while (*str )
//	{
//		hash = hash * seed + (* str++);
//	}
//	return (hash & 0x7FFFFFFF);
//}
//
//template<class K>
//struct HashFuner
//{
//	size_t operator() (const K& key)
//	{
//		return key;
//	}
//};
//
//template<>
//struct HashFuner<string>
//{
//	size_t operator() (const string& key)
//	{
//		return BKDRHash(key.c_str());
//	}
//};
//
//template<class K, class HashFun = HashFuner<K> >
//class HashTable
//{
//public:
//	HashTable()
//		:_tables(NULL)
//		,_size(0)
//		,_capacity(0)
//		,_status(0)
//	{}
//
//	HashTable(size_t capacity)
//		:_tables(new K[capacity])
//		,_size(0)
//		,_capacity(capacity)
//		,_status(new Status[capacity])
//	{
//		//memset(_status, EMPTY, capacity);
//		for (size_t i = 0; i < capacity; ++i)
//		{
//			_status[i] = EMPTY;
//		}
//	}
//
//	~HashTable()
//	{
//		if (_tables)
//		{
//			delete[] _tables;
//			delete[] _status;
//		}
//	}
//public:
//	bool Insert(const K& key)
//	{
//		// 检查负载因子，考虑是否要增容
//		if (_size*10/_capacity >= 8)
//		{
//			//_capacity = 2*_capacity;
//			//K* newTables = new K[_capacity];
//
//			HashTable<K, HashFun> newTables(2*_capacity);
//			for (size_t i = 0 ; i < _capacity; ++i)
//			{
//				if (_status[i] == EXITS)
//				{
//					newTables.Insert(_tables[i]);
//				}
//			}
//
//			this->Swap(newTables);
//		}
//
//		size_t index = HashFunc(key);
//		while (_status[index] == EXITS)
//		{
//			++index;
//			if (index == _capacity)
//			{
//				index = 0;
//			}
//		}
//
//		_tables[index] = key;
//		_status[index] = EXITS;
//		_size++;
//
//		return true;
//	}
//
//	bool Remove(const K& key)
//	{
//		size_t index = HashFunc(key);
//		while (_status[index] != EMPTY)
//		{
//			if (_tables[index] == key)
//			{
//				_status[index] = DELETE;
//				return true;
//			}
//
//			++index;
//			if (index == _capacity)
//			{
//				index = 0;
//			}
//		}
//
//		return false;
//	}
//
//	bool Find(const K& key)
//	{
//		size_t index = HashFunc(key);
//		while (_status[index] != EMPTY)
//		{
//			if (_tables[index] == key)
//			{
//				if (_status[index] == EXITS)
//				{
//					return true;
//				}
//				else
//				{
//					false;
//				}
//			}
//
//			++index;
//			if (index == _capacity)
//			{
//				index = 0;
//			}
//		}
//
//		return false;
//	}
//
//	bool Find2(const K& key)
//	{
//		//size_t index = HashFunc(key);
//		int i = 0;
//		//size_t index = HashFunc2(key, 0);
//		size_t index = HashFunc0(key);
//		while (_status[index] != EMPTY)
//		{
//			if (_tables[index] == key)
//			{
//				if (_status[index] == EXITS)
//				{
//					return true;
//				}
//				else
//				{
//					false;
//				}
//			}
//
//			index = HashFunc2(index, ++i);
//		}
//
//		return false;
//	}
//
//	size_t HashFunc(const K& key)
//	{
//		HashFun hf;
//		return hf(key) % _capacity;
//	}
//
//	//size_t HashFunc2(const K& key, size_t i)
//	//{
//	//	// int
//	//	HashFun hf;
//	//	return (hf(key) + i*i) % _capacity;
//	//}
//
//	size_t HashFunc0(const K& key)
//	{
//		// int
//		HashFun hf;
//		return (hf(key)) % _capacity;
//	}
//
//	size_t HashFunc2(size_t prevHashValue, int i)
//	{
//		// int
//		return (prevHashValue+2*i-1) % _capacity;
//	}
//
//
//
//	void Swap(HashTable<K, HashFun>& ht)
//	{
//		swap(_tables, ht._tables);
//		swap(_status, ht._status);
//		swap(_size, ht._size);
//		swap(_capacity, ht._capacity);
//	}
//
//	void Print()
//	{
//		for (size_t i = 0; i < _capacity; ++i)
//		{
//			cout<<_status[i]<<":";
//			cout<<_tables[i]<<"  ";
//		}
//
//		cout<<endl;
//	}
//
//protected:
//	K* _tables;			// 散列表
//	size_t _size;		// 数据的个数
//	size_t _capacity;	// 容量
//
//	Status* _status;	// 数据状态表
//};
//
////struct HashFunerString
////{
////	size_t operator() (const string& key)
////	{
////		// "abcd"
////		// "bcda"
////	/*	size_t value = 0;
////		for (size_t i = 0; i < key.size(); ++i)
////		{
////			value += abs(key[i]);
////		}*/
////
////		size_t value = BKDRHash(key.c_str());
////		return value;
////	}
////};
//
//void TestHashTable()
//{
//	HashTable<int> ht1(10);
//	ht1.Insert(89);
//	ht1.Insert(18);
//	ht1.Insert(49);
//	ht1.Insert(58);
//	ht1.Insert(9);
//
//	ht1.Print();
//
//	ht1.Remove(58);
//
//	ht1.Print();
//
//	cout<<"Find 9?"<<ht1.Find(9)<<endl;
//
//	HashTable<string> ht2(10);
//	ht2.Insert("字典");
//	ht2.Insert("词典");
//	ht2.Insert("abcd");
//	ht2.Insert("bcda");
//};

// K -> 线性探测
// KV -> 二次探测

#pragma once

enum Status
{
	EXITS,
	DELETE,
	EMPTY,
};

template<class K, class V>
class KeyValueNode
{
	K _key;
	V _value;

	KeyValueNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
	{}
};

template<class K, class V, class HashFun = HashFuner<K> >
class HashTable
{
	typedef KeyValueNode<K, V> KVNode;
public:
	HashTable()
		:_tables(NULL)
		,_size(0)
		,_capacity(0)
		,_status(0)
	{}

	HashTable(size_t capacity)
		:_tables(new KVNode[capacity])
		,_size(0)
		,_capacity(capacity)
		,_status(new Status[capacity])
	{
		for (size_t i = 0; i < capacity; ++i)
		{
			_status[i] = EMPTY;
		}
	}

	HashTable(const HashTable<K, V>& ht)
		:_tables(NULL)
		,_status(NULL)
	{
		HashTable<K,V> newTables(ht._capacity);
		for (size_t i = 0; i < ht._capacity; ++i)
		{
			if (ht._status[i] == EXITS)
			{
				newTables.Insert(ht._tables[i]);
			}
		}
	
		this->Swap(newTables);
	}

	HashTable<K, V>& operator=(HashTable<K, V> ht)
	{
		this->Swap(ht);

		return *this;
	}

	~HashTable()
	{
		if (_tables)
		{
			delete[] _tables;
			delete[] _status;
		}
	}
public:
	bool Insert(const K& key, const V& value)
	{
		// 负载因子 -- 增容 

		size_t index = HashFunc0(key);
		int i = 1;
		while(_status[index] == EXITS)
		{
			index = HashFunc2(index, i++);
		}

		_tables[index] = KVNode(key, value);
		_status[index] = EXITS;
		_size++;

	}

	bool Remove(const K& key)
	{
		size_t index = HashFunc0(key);
		int i = 1;
		while (_tables[index] != EMPTY)
		{
			if (_tables[index]._key == key)
			{
				if (_status[index] == EXITS)
				{
					--_size;
					_status[index] = DELETE;
					return true;
				}
				else
				{
					return false;
				}
			}
			
			index = HashFunc2(index, i++);
		}

		return false;
	}

	KVNode* Find(const K& key)
	{
		size_t index = HashFunc0(key);
		int i = 1;
		while (_status[index] != EMPTY)
		{
			if (_tables[index]._key == key)
			{
				if (_status[index] == EXITS)
					return true;
				else
					return false;
			}

			index = HashFunc2(index, i++);
		}

		return false;
	}

	size_t HashFunc0(const K& key)
	{
		return HashFun()(key) % _capacity;
	}

	size_t HashFunc2(size_t prevValue, int i)
	{
		return (prevValue+2*i-1) % _capacity;
	}


	void Swap(HashTable<K, V, HashFun>& ht)
	{
		swap(_tables, ht._tables);
		swap(_status, ht._status);
		swap(_size, ht._size);
		swap(_capacity, ht._capacity);
	}

protected:
	KVNode* _tables;			// 散列表
	size_t _size;				// 数据的个数
	size_t _capacity;			// 容量

	Status* _status;			// 数据状态表
};

void TestHashTable()
{
	HashTable<string, string> ht1(10);
	ht1.Insert("相交", "xiangjiao");

	KeyValueNode<string, string>* ret = ht1.Find("相交");
	ret->_value = "Cross";
};