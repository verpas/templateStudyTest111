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
#define expend(x) x
#define Typelist_1(a) TypeList<a,NullType>
#define Typelist_2(a,b) TypeList<a,Typelist_1(b)>
#define Typelist_3(a,b,c) TypeList<a,Typelist_2(b,c)>
#define Typelist_4(a,b,c,d) TypeList<a,Typelist_3(b,c,d)>
#define Typelist_5(a,b,c,d,e) TypeList<a,Typelist_4(b,c,d,e)>
// #define Typelist_2(a,b) TypeList<a,TypeList<b,NullType>>
// #define Typelist_3(a,b,c) TypeList<a,TypeList<b,TypeList<c,NullType>>>
// #define Typelist_4(a,b,c,d) TypeList<a,TypeList<b,TypeList<c,TypeList<d,NullType>>>>

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
template<class Head>
struct TypeAt<TypeList<Head, NullType>, 0>
{
	typedef Head Result;
};
template<class Head,  unsigned int i>
struct TypeAt<TypeList<Head, NullType>, i>
{
	typedef typename NullType Result;
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
#include <queue>
class FixedAllocator
{
public:
	void* Allocate();
	FixedAllocator(std::size_t blockSize,
	unsigned char numBlocks) :blockSize_(blockSize),numBlocks_(numBlocks)
	{}
	void Deallocate(void * p);
private:
	std::size_t blockSize_;
	unsigned char numBlocks_;
	typedef std::vector<Chunk> Chunks;
	Chunks chunks_;
	Chunk* allocChunt_;
	Chunk* deallocChunk_;
	std::queue<void *> deallocQue;
};
void FixedAllocator::Deallocate(void * p)
{
	deallocQue.push(p);
}
void * FixedAllocator::Allocate()
{
	if (!deallocQue.empty())
	{
		void * temp =  deallocQue.front();
		deallocQue.pop();
		return temp;
	}
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
	SmallObjectAllocator(std::size_t chunkSize, std::size_t max_objectSize);
	void * Allocate(std::size_t numBytes);
	void Deallocate(void * p, std::size_t size);
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
//#define MACRO_ARGS(...)     __VA_ARGS__
#define EXPAND(...) __VA_ARGS__
#define MACRO_ARGS_FILTER(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_N, ...) _N
//#define MACRO_ARGS_CONTER(...)  MACRO_ARGS_FILTER(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define MACRO_ARGS_(e)        e
#define MACRO_ARGS_CONTER(...)  MACRO_ARGS_(MACRO_ARGS_FILTER(0, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define MACRO_CAT(x, y)     x##y

#define MACRO_GLUE( y)    MACRO_CAT(Typelist_,y)
#define MACRO_add(x,y)    MACRO_CAT(x,y)
#define type_all(...)    MACRO_ARGS_(MACRO_GLUE(MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

#define becomestr(x) #x
#define line2str(x,y) becomestr(x##1)
#define isempty(...) \
if(line2str(__VA_ARGS__,1)=="1")\
  cout<<"True"<<endl;\
else\
 cout << "false"<<endl;
namespace MyFunctional
{
// 	template<class ResultType>
// 	class Functor {
// 	public:
// 		ResultType operator()() {};
// 	};
#define num(x)  typedef typename TypeAt<TList, x-1>::Result MACRO_add(Param,x);
#define operatorFun(...) MACRO_ARGS_((*spImpl_)(__VA_ARGS__));
	template <typename T1,typename T2>
	class FunctionImpl{};
	template <typename R>
	class FunctionImpl<R, NullType>
	{
	public:
		virtual R operator ()() = 0;
		virtual FunctionImpl* clone() const = 0;
		virtual ~FunctionImpl(){}
	};
	template <typename R, typename P1>
	class FunctionImpl<R, Typelist_1(P1)>
	{
	public:
		virtual R operator ()(P1) = 0;
		virtual FunctionImpl* clone() const = 0;
		virtual ~FunctionImpl(){}
	};
	template <typename R, typename P1,typename P2>
	class FunctionImpl<R, Typelist_2(P1,P2)>
	{
	public:
		virtual R operator ()(P1,P2) = 0;
		virtual FunctionImpl* clone() const = 0;
		virtual ~FunctionImpl(){}
	};
	template<class ParentFunctor,typename Fun>
	class FunctorHandler :
		public FunctionImpl<typename ParentFunctor::ResultType, typename ParentFunctor::ParamList>
	{
		Fun fun_;
	public:
		typedef typename ParentFunctor::ResultType ResultType;
		FunctorHandler(const Fun& fun):fun_(fun){}
		ResultType operator()() {
			return fun_();
		}
		ResultType operator()(typename ParentFunctor::Param1 p1) {
			return fun_(p1);
		}
		ResultType operator()(typename ParentFunctor::Param1 p1, typename ParentFunctor::Param2 p2) {
			return fun_(p1,p2);
		}
		FunctorHandler * clone() const { return new FunctorHandler(*this); }
	};
	template<class ParentFunctor,typename Obj , typename PointerToMemFn>
	class MemFunHandler
		:public FunctionImpl<typename ParentFunctor::ResultType, typename ParentFunctor::ParamList>
	{
		Obj * pObj_;
		PointerToMemFn pMemFn_;
	public:
		typedef typename ParentFunctor::ResultType ResultType;
		MemFunHandler(Obj*  pObj, const PointerToMemFn & pMemFn)
			:pObj_(pObj),pMemFn_(pMemFn)
		{

		}
		MemFunHandler * clone() const { return new MemFunHandler(*this); }
		ResultType operator()() {
			return ((*pObj_).*pMemFn_)();
		}
		ResultType operator()(typename ParentFunctor::Param1 p1) {
			return ((*pObj_).*pMemFn_)(p1);
		}
		ResultType operator()(typename ParentFunctor::Param1 p1, typename ParentFunctor::Param2 p2) {
			return ((*pObj_).*pMemFn_)(p1, p2);
		}

	};
	template <typename R , typename TList>
	class Functor 
	{
	
	private: 
		typedef  FunctionImpl<R, TList> Impl;
		
		
		std::auto_ptr<Impl> spImpl_;
	public:
		Functor();
		Functor(const Functor&);
		Functor& operator=(const Functor &);
		explicit Functor(std::auto_ptr<Impl> spImpl);
		typedef TList ParamList;
		typedef R ResultType;
		typedef typename TypeAt<TList, 0>::Result Param1;
		num(2); num(3); num(4); num(6); num(5); num(7); num(8);
		R operator ()() {
			return operatorFun();
		}
		R operator ()(Param1 p1) {
			return operatorFun(p1);
		}
		R operator ()(Param1 p1,Param2 p2) {
			return operatorFun(p1,p2);
		}
		template<class Fun>
		Functor(const Fun& fun) :spImpl_(new FunctorHandler<Functor, Fun>(fun)) 
		{

		};
		template<typename member,typename Fun>
		Functor(member * mem,const Fun& fun) :spImpl_(new MemFunHandler<Functor, member , Fun>(mem,fun))
		{

		};
	};
	template <typename R>
	class Functor<R,NullType>
	{

	private:
		typedef  FunctionImpl<R,NullType > Impl;


		std::auto_ptr<Impl> spImpl_;
	public:
		Functor();
		Functor(const Functor&);
		Functor& operator=(const Functor &);
		explicit Functor(std::auto_ptr<Impl> spImpl);
		typedef NullType ParamList;
		typedef R ResultType;
		typedef typename NullType Param1;
		typedef typename NullType Param2;
		R operator ()() {
			return operatorFun();
		}
		template<class Fun>
		Functor(const Fun& fun) :spImpl_(new FunctorHandler<Functor, Fun>(fun))
		{

		};
		template<typename member, typename Fun>
		Functor(member * mem, const Fun& fun) :spImpl_(new MemFunHandler<Functor, member, Fun>(mem, fun))
		{

		};
	};
// 	template<class Incoming>
// 	class BinderFirst :
// 		public FunctionImpl<typename Incoming::ResultType, typename Incoming::ParamList::Tail >
// 	{
// 		typedef Functor<typename Incoming::ResultType, Incoming::ParamList::Tail> Outgoing;
// 		typedef typename Incoming::Param1 Bound;
// 		typedef typename Imcoming::ResultType ResultType;
// 	public:
// 		BinderFirst(const Incoming & fun, Bound bound) :fun_(fun), bound_(bound) {}
// 		BinderFirst * clone()const { return new BinderFirst(*this); }
// 		ResultType operator()()
// 		{
// 			return fun_(bound_);
// 		}
// 		ResultType operator()(typename Outgoing::Param1 p1)
// 		{
// 			return fun_(bound_,p1);
// 		}
// 	private:
// 		Incoming fun_;
// 		Bound bound_;
// 	};
// 	template<class Functor>
// 	typename private::BinderFirstTraits<Functor>::BoundFunctorType
// 		BindFirst()
};
struct  TestFunctor
{
	void operator()(int i , double d)

	{
		cout << "test int  = " << i << "\t double = " << d << endl;
	}
};
class Parrot
{
public:
	void Eat() { cout << "eat" << endl; }
	void Speak() { cout << "speak" << endl; }
};
void testfun(const int& i, double d)
{
	cout << "test fun" << "\t int = " << i << "\t double = " << d << endl;
}
struct MemControlBlock
{
	std::size_t size_:31;
	bool available:1;
};
int main()
{
	//printf();
	TestFunctor f;
	MyFunctional::Functor <void, Typelist_2(int, double)> cmd(f);
	cmd(1, 1.1);

	MyFunctional::Functor <void, Typelist_2(const int&, double)> cmd2(&testfun);
	cmd2(1, 1.1);


	Parrot parrot;
	MyFunctional::Functor<void,NullType> cmd3(&parrot, &Parrot::Eat),
		cmd4(&parrot, &Parrot::Speak);
	cmd3();
	cmd4();
	int ParamCount = MACRO_ARGS_CONTER(int,double,char);
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
	isempty(int, char);
	isempty();
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
	
	std::cout << "typename==="<<typeid(Typelist_4(int,int, double, char)).name()<<std::endl;
	static_cast<int>('5');
	std::cout << constreferenceType<int>::isconstreference << std::endl;
	std::cout << constreferenceType<int&>::isconstreference << std::endl;
	std::cout << constreferenceType<const int&>::isconstreference << std::endl;
	std::cout << Length<type_all(int, double, char, long)>::value << std::endl;
	std::cout << typeid(TypeAt<type_all(int, double, char, long), 3>::Result).name() << std::endl;
	std::cout << typeid(TypeAt<type_all(int, double, char, long), 4>::Result).name() << std::endl;
	std::cout << typeid(TypeAt<type_all(int, double, char, long), 5>::Result).name() << std::endl;
	std::cout << IndexOf<type_all(int, double, char, long), int>::value << std::endl;
	std::cout << typeid(AppendList<type_all(int, double, char, long), int>::Result).name() << std::endl;
	std::cout << typeid(EraseType<type_all(int, double, char, long), float>::Result).name() << std::endl;
	std::cout << typeid(NoSameType<type_all(int, double, int,double)>::Result).name() << std::endl;
    return 0;
}