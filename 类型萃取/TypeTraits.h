#pragma once

struct __TrueType
{
	bool Get()
	{
		return true;
	}
};

struct __FalseType
{
	bool Get()
	{
		return false;
	}
};

template <class _Tp>
struct TypeTraits
{
	typedef __FalseType  __IsPODType;
};

template <>
struct TypeTraits<char>
{
	typedef __TrueType  __IsPODType;
};

template <>
struct TypeTraits<int>
{
	typedef __TrueType  __IsPODType;
};

template <>
struct TypeTraits<bool>
{
	typedef __TrueType  __IsPODType;
};


//template<class T>
//void _Copy(T* src, T* dst, size_t size, __TrueType)
//{
//	// 基本类型 == POD
//	cout<<"POD"<<endl;
//	memcpy(dst, src, sizeof(T)*size);
//}
//
//template<class T>
//void _Copy(T* src, T* dst, size_t size, __FalseType)
//{
//	// 自定义类型
//	cout<<"NON_POD"<<endl;
//	for (size_t i = 0; i < size; ++i)
//	{
//		dst[i] = src[i];
//	}
//}
//
//template<class T>
//void Copy(T* src, T* dst, size_t size)
//{
//	_Copy(src, dst, size, TypeTraits<T>::__IsPODType() );
//}

template<class T>
void Copy(T* src, T* dst, size_t size)
{
	// 1:int
	if (TypeTraits<T>::__IsPODType().Get())
	{
		cout<<"POD"<<endl;
		memcpy(dst, src, sizeof(T)*size);
	}
	else
	{
		cout<<"NON_POD"<<endl;
		for (size_t i = 0; i < size; ++i)
		{
			dst[i] = src[i];
		}
	}
}

//void Test()
//{
//	int src1[10] = {1};
//	int dst1[10] = {2};
//
//	Copy(src1, dst1, 10);
//
//	string src2[10] = {"1"};
//	string dst2[10] = {"2"};
//
//	Copy(src2, dst2, 10);
//}
