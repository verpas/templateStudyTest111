// templateStudyTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include <assert.h>
template<class T>
class List 
{
public:
	template<class T2>
	List(List<T2> const&);
};
template<class T>
	template<class T2>
List<T>::List(List<T2>const & a)
{

}
template<typename T>
int length(List<T> const &)
{

}

class Collection {
public:
	template<typename T>
	class Node{
	public :
		T d;
	};
	template<typename T>
	class Handle;

	template<typename T>
	T * alloc()
	{

	}
};
template<typename T>
class Collection::Handle
{

};


template< class T>
class  abc
{
public:
	T h;
	char ggg[sizeof(T)];
	int size = sizeof(T);
};
template<int H>
int fff()
{
	printf("%d\n", H);
	if(H>0)
		return 1 + fff<H-1>();
}
template<>
int fff<0>()
{
	return 1;
}
/*template<int T>
class oo 
{
	const int k = 1 + oo<T - 1>::k;
};
template<>
class oo<0>
{
	const int k =1;
};*/
template<template<typename T> class Y>//模板的模板参数
class test
{
	Y<int> g;
};

template<class T> 
void add(T a)
{
	int h = a;
	std::cout << "T" << std::endl;
}

template<>
void add<int *>(int * f)
{
	int *h = f;
	std::cout << "T*" << std::endl;
}



using namespace std;
template<class T>
class testSFINAE
{
	typedef typename T x;
};
template < class T >
void testsfi(typename T::x i)
{
	cout << "T::X" << endl;
}
template<class T>
void testsfi(T f)
{
	cout << "T" << endl;
}
template<typename T>
class referenceType 
{
private:
	template<typename T>
	struct reference { enum { isreference = false }; };
	template<typename T>
	struct reference<T&> { enum { isreference = true }; };
public:
	enum 
	{
		isreference = reference<T>::isreference
	};
};




template<typename T>
class constreferenceType
{
private:
	template<typename T>
	struct constreference { enum { isconstreference = false }; };
	template<typename T>
	struct constreference<const T&> { enum { isconstreference = true }; };
public:
	enum
	{
		isconstreference = constreference<T>::isconstreference
	};
};

class NullType {};
struct EmptyType{};
template<class T,class U>
struct TypeList
{
	typedef T Head;
	typedef U Tail;
};
#define Typelist_1(a) TypeList<a,NullType>
#define Typelist_2(a,b) TypeList<a,TypeList<b,NullType>>
#define Typelist_3(a,b,c) TypeList<a,TypeList<b,TypeList<c,NullType>>>
#define Typelist_4(a,b,c,d) TypeList<a,TypeList<b,TypeList<c,TypeList<d,NullType>>>>

template<class TList> struct Length {};
template<>struct Length<NullType>
{
	enum { value = 0 };
};
template<class T,class U>
struct Length<TypeList<T, U>>
{
	enum {value = 1+Length<U>::value};
};


template<class TList, unsigned int index> struct TypeAt;
template<class Head,class Tail>
struct TypeAt<TypeList<Head, Tail>, 0>
{
	typedef Head Result;
};

template<class Head, class Tail,unsigned int i>
struct TypeAt<TypeList<Head, Tail>, i>
{
	typedef typename TypeAt<Tail,i-1>::Result Result;
};


template<class TList,class T>
struct IndexOf{
	enum { value = -1 };
};
template<class Tail,class T>
struct IndexOf<TypeList<T, Tail>, T>
{
	enum {value = 0};
};
template<class Head,class Tail , class T>
struct IndexOf<TypeList<Head, Tail>, T>
{
private:
	enum { temp = IndexOf < Tail,T >::value };
public:
	enum{value = temp==-1?-1:1+temp};
};






template<class T,class U>
struct AppendList ;


template<>
struct AppendList<NullType, NullType>
{
	typedef NullType Result;
};


template<class T>
struct AppendList<NullType, T>
{
	typedef Typelist_1(T) Result;
};


template<class Head,class Tail>
struct AppendList<NullType, TypeList<Head, Tail>>
{
	typedef  TypeList<Head, Tail> Result;
};


template<class Head,class Tail,class T>
struct AppendList<TypeList<Head, Tail>,T >
{
	typedef TypeList< Head, typename AppendList<Tail, T>::Result> Result;
};


template<class T,class U>
struct EraseType { typedef T Result; };

template<class T> struct EraseType<NullType, T>
{
	typedef NullType Result;
};

template<class Tail, class T>
struct EraseType<TypeList<T, Tail>, T>
{
	typedef Tail Result;
};
template<class Head,class Tail , class T>
struct EraseType<TypeList<Head, Tail>, T>
{
	typedef TypeList<Head, typename EraseType<Tail, T>::Result> Result;
};


template<class T, class U>
struct EraseAllType { typedef T Result; };

template<class T> struct EraseAllType<NullType, T>
{
	typedef NullType Result;
};

template<class Tail, class T>
struct EraseAllType<TypeList<T, Tail>, T>
{
	typedef typename EraseAllType<Tail,T>::Result Result;
};
template<class Head, class Tail, class T>
struct EraseAllType<TypeList<Head, Tail>, T>
{
	typedef TypeList<Head, typename EraseAllType<Tail, T>::Result> Result;
};


template<class T>struct  NoSameType
{};
template<> struct NoSameType<NullType>
{
	typedef NullType Result;
};
template<class Head,class Tail>
struct  NoSameType<TypeList<Head, Tail>>
{
private:
	typedef typename NoSameType<Tail>::Result L1;
	typedef typename EraseType<L1, Head>::Result L2;
public:
	typedef TypeList<Head, L2> Result;
};




template<class T>
struct Holder
{
	T value_;
};

template<class TList,template <class > class Unit>
 class GenScatterHierarchy;

template<class T1,class T2, template<class > class Unit>
class GenScatterHierarchy<TypeList<T1,T2>,Unit>
	:public GenScatterHierarchy<T1,Unit>
	,public GenScatterHierarchy<T2,Unit>
{

};
template<class AtomicType, template <class > class Unit>
class GenScatterHierarchy:public Unit<AtomicType>
{

};
template<template<class> class Unit>
class GenScatterHierarchy<NullType,Unit>
{};

typedef GenScatterHierarchy<Typelist_4(int, int,long,double), Holder> MyINfo;


template<class T,class TList,template<class> class Unit>
Unit<T>& Field(GenScatterHierarchy<TList, Unit>& obj)
{
	return obj;
}
template<int V>
struct  Int2Type
{
	enum {value = V};

};

template<class Head,class Tail, template <class > class Unit>
Unit<Head> & FieldHelper(GenScatterHierarchy<TypeList<Head,Tail>,Unit> & obj,Int2Type<0>)
{
	GenScatterHierarchy<Head, Unit> & leftBase = obj;
	return leftBase;
}


template<int i , class Head, class Tail, template<class>class Unit >
Unit<typename TypeAt<TypeList<Head, Tail>, i>::Result>& FieldHelper(GenScatterHierarchy<TypeList<Head, Tail>, Unit> & obj, Int2Type<i>)
{
	GenScatterHierarchy<Tail, Unit>& rightbase = obj;
	return FieldHelper(rightbase, Int2Type<i - 1>());
}



template<int i , class TList,template<class> class Unit>
Unit<typename TypeAt<TList, i>::Result>& Field(GenScatterHierarchy<TList, Unit>& obj)
{
	return FieldHelper(obj, Int2Type<i>());
}



struct Chunk {
	void Init(std::size_t blockSize, unsigned char blocks);
	void Release();
	void *Allocate(std::size_t blockSize);
	void Deallocate(void * p, std::size_t blockSize);
	unsigned char * pData_;
	unsigned char fristAvailableBlock_, blocksAvailable_;

};
void Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
	pData_ = new unsigned char[blockSize *blocks];
	fristAvailableBlock_ = 0;
	blocksAvailable_ = blocks;
	unsigned char i = 0;
	unsigned char * p = pData_;
	for (; i != blocks; p+=blockSize)
	{
		*p = ++i;
	}
}
void *Chunk::Allocate(std::size_t blockSize)
{
	if (!blocksAvailable_) return 0;
	unsigned char * pResult = pData_ + (fristAvailableBlock_ * blockSize);
	fristAvailableBlock_ = *pResult;
	--blocksAvailable_;
	return pResult;
}

void Chunk::Deallocate(void * p, std::size_t blockSize)
{
	assert(p >= pData_);
	unsigned char * toRelease = static_cast<unsigned char *>(p);
	assert((toRelease-pData_)%blockSize==0);
	*toRelease = fristAvailableBlock_;
	fristAvailableBlock_ = static_cast<unsigned char>((toRelease - pData_) / blockSize);
	assert(fristAvailableBlock_==((toRelease-pData_)/blockSize));
	++blocksAvailable_;
}
class FixedAllocator
{
public:
	void* Allocate();
private:
	std::size_t blockSize_;
	unsigned char numBlocks_;
	typedef std::vector<Chunk> Chunks;
	Chunks chunks_;
	Chunk* allocChunt_;
	Chunk* deallocChunk_;
};
void * FixedAllocator::Allocate()
{
	if (allocChunt_ == 0 || allocChunt_->blocksAvailable_ == 0)
	{
		Chunks::iterator i = chunks_.begin();
		for (;; ++i)
		{
			if (i == chunks_.end())
			{
				chunks_.push_back(Chunk());
				Chunk& newChunk = chunks_.back();
				newChunk.Init(blockSize_, numBlocks_);
				allocChunt_ = &newChunk;
				deallocChunk_ = &chunks_.front();
				break;
			}
			if (i->blocksAvailable_ > 0)
			{
				allocChunt_ = &*i;
				break;
			}
		}
	}
	assert(allocChunt_ != 0);
	assert(allocChunt_->blocksAvailable_ > 0);
	return allocChunt_->Allocate(blockSize_);
}
class SmallObjectAllocator {
private:
	FixedAllocator * pLastAlloc;
	FixedAllocator * pLastDealloc;
	std::vector<FixedAllocator> pool_;
};
class SmallObject
{
public:
	static void * operator new(std::size_t size);
	static void operator delete(void *p, std::size_t size);
	virtual ~SmallObject();
};
class testaaa
{
	int h;
public:
	void * operator new(std::size_t size)
	{
		cout << "new test  size = " <<size<< endl;
		return ::new testaaa;
	}
	void * operator new[](std::size_t size,void * ptr)
	{
		cout << "new[] test  size = " << size << endl;
	return ::new testaaa[size/sizeof(testaaa)];
	}
	void operator delete(void *p, std::size_t size)
	{
		cout << "delete size test" << endl;
		::delete p;
	}
	void operator delete(void *p)
	{
		cout << "delete test" << endl;
		::delete p;
	}
	virtual ~testaaa() {};
};
namespace MyFunctional
{
	template<class ResultType>
	class Functor {
	public:
		ResultType operator()() {};
	};
}



struct MemControlBlock
{
	std::size_t size_:31;
	bool available:1;
};

int main()
{
// 	std::cout << 123 << std::endl;
// 	int ret = fff<100>();
// 	//oo<100> j;
// 	test<abc> j;
// 	int *h =NULL;
// 	add(123);
// 	add(h);
// 	testSFINAE<int> testaa;
// 	testsfi(testaa);
// 	testsfi(33432432);
// 	int ttttttttt = sizeof(testaaa);
// 	testaaa * p = new testaaa;
// 	delete p;
// 	p = new(p) testaaa[5];
// 	delete[] p;
	cout << sizeof(MemControlBlock) << endl;
	std::tuple<int,int>;
	MyINfo temp;
	//auto t = temp.value_;
	//auto a = Field<int>(temp);
	auto b  = Field<0>(temp).value_;
	auto c = Field<1>(temp).value_;
	auto name = (static_cast<Holder<double>&>(temp)).value_;
	std::cout << referenceType<int>::isreference << std::endl;
	std::cout << referenceType<int&>::isreference << std::endl;
	std::cout << referenceType<const int&>::isreference << std::endl;


	static_cast<int>('5');
	std::cout << constreferenceType<int>::isconstreference << std::endl;
	std::cout << constreferenceType<int&>::isconstreference << std::endl;
	std::cout << constreferenceType<const int&>::isconstreference << std::endl;
	std::cout << Length<Typelist_4(int, double, char, long)>::value << std::endl;
	std::cout << typeid(TypeAt<Typelist_4(int, double, char, long), 3>::Result).name() << std::endl;
	std::cout << IndexOf<Typelist_4(int, double, char, long), int>::value << std::endl;
	std::cout << typeid(AppendList<Typelist_4(int, double, char, long), int>::Result).name() << std::endl;
	std::cout << typeid(EraseType<Typelist_4(int, double, char, long), float>::Result).name() << std::endl;
	std::cout << typeid(NoSameType<Typelist_4(int, double, int,double)>::Result).name() << std::endl;
    return 0;
}