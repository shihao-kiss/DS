#pragma once
#include <vector>

// 压缩存储
template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* a, size_t n)
		:_array(new T[n*(n+1)/2])
		,_n(n)
	{
		size_t index = 0;
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				if (i >= j)
				{
					_array[index++] = a[i*n+j] ;
				}
				else
				{
					break;
				}
			}
		}
	}

	void Display()
	{
		for (size_t i = 0; i < _n; ++i)
		{
			for (size_t j = 0; j < _n; ++j)
			{
				if (i >= j)
				{
					cout<<_array[i*(i+1)/2 +j]<<" ";
				}
				else
				{
					cout<<_array[j*(j+1)/2 +i]<<" ";
				}
			}

			cout<<endl;
		}

		cout<<endl;
	}

	T& AccessNum(size_t i, size_t j)
	{
		assert(i < _n);
		assert(j < _n);

		if (i < j)
		{
			swap(i, j);
		}

		return _array[i*(i+1)/2 +j];
	}

	~SymmetricMatrix()
	{
		if (_array)
		{
			delete[] _array;
		}
	}



private:
	T* _array;  // 对称矩阵的压缩存储的一维数据
	size_t _n;	// 对称矩阵的行列数
};

void Test1()
{
	int a[5][5] = 
	{
		{0, 1, 2, 3, 4},
		{1, 0, 1, 2, 3},
		{2, 1, 0, 1, 2},
		{3, 2, 1, 0, 1},
		{4, 3, 2, 1, 0},
	};

	SymmetricMatrix<int> sm((int*)a, 5);
	sm.Display();
}

template<class T>
struct Trituple
{
	int _row;
	int _col;
	T _value;
};

template<class T>
class SparseMatrix
{
public:	
	SparseMatrix()
		:_colSize(0)
		,_rowSize(0)
	{}

	SparseMatrix(T* a, size_t m, size_t n, const T& invalid)
		:_rowSize(m)
		,_colSize(n)
		,_invalid(invalid)
	{
		for (size_t i = 0; i < m; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				if (a[i*n+j] != invalid)
				{
					Trituple<T> t;
					t._row = i;
					t._col = j;
					t._value = a[i*n+j];

					_array.push_back(t);
				}
			}
		}
	}

	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _rowSize; ++i)
		{
			for (size_t j = 0; j < _colSize; ++j)
			{
				if (index < _array.size()
					&& _array[index]._row == i 
					&& _array[index]._col == j)
				{
					cout<<_array[index++]._value<<" ";
				}
				else
				{
					cout<<_invalid<<" ";
				}
			}

			cout<<endl;
		}

		cout<<endl;
	}

	SparseMatrix<T> Transpose()
	{
		SparseMatrix<T> sm;
		sm._colSize = _rowSize;
		sm._rowSize = _colSize;
		sm._invalid = _invalid;

		// O(colSize*有效数据的个数)
		for (size_t i = 0; i < _colSize; ++i)
		{
			size_t index = 0;
			while (index < _array.size())
			{
				if (_array[index]._col == i)
				{
					Trituple<T> t;
					t._row = _array[index]._col;
					t._col = _array[index]._row;
					t._value = _array[index]._value;
					sm._array.push_back(t);
				}

				++index;
			}
		}

		return sm;
	}

	// O(有效数据个数+colsize)
	SparseMatrix<T> FastTranspose()
	{
		SparseMatrix<T> sm;
		sm._colSize = _rowSize;
		sm._rowSize = _colSize;
		sm._invalid = _invalid;

		int* rowCounts = new int[_colSize];
		int* rowStart = new int[_colSize];
		memset(rowCounts, 0, sizeof(int)*_colSize);
		memset(rowStart, 0, sizeof(int)*_colSize);

		size_t index = 0;
		while (index < _array.size())
		{
			rowCounts[_array[index]._col]++;
			++index;
		}

		rowStart[0] = 0;
		for (int i = 1; i < _colSize; ++i)
		{
			rowStart[i] = rowStart[i-1] + rowCounts[i-1];
		}

		// 借助rowStart定位转置后压缩存储的位置
		index = 0;
		sm._array.resize(_array.size());
		while (index < _array.size())
		{
			size_t begin = rowStart[_array[index]._col];
			Trituple<T> t;
			t._col = _array[index]._row;
			t._row = _array[index]._col;
			t._value = _array[index]._value;

			sm._array[begin] = t;

			++rowStart[_array[index]._col];
			++index;
		}
		
		delete[] rowCounts;
		delete[] rowStart;

		return sm;
	}

private:
	//Trituple* _array;	// 压缩存储
	//size_t _size;		// 稀疏矩阵的有效数据的个数

	vector<Trituple<T>> _array;
	size_t _rowSize;
	size_t _colSize;
	T _invalid;	
};

void Test2()
{
	int a[6][5] =
	{
		{1,0,3,0,5},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{2,0,4,0,6},	
		{0,0,0,0,0},
		{0,0,0,0,0},
	};

	SparseMatrix<int> sm1((int*)a, 6, 5, 0);
	sm1.Display();

	SparseMatrix<int> sm2 = sm1.FastTranspose();
	sm2.Display();
}