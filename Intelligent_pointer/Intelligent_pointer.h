#pragma once

//模板化，可以接收任类型
template<class T>
class L_autoPtr
{
	T* obj = nullptr;
public:
	//构造方法，赋值一个指针
	L_autoPtr(T* ptr) :obj(ptr)
	{
	}
	//析构方法，释放指针
	~L_autoPtr()
	{
		delete obj;
	}
	//不标准的复制构造（转移内部指针控制权）
	L_autoPtr(L_autoPtr<T>& ptr)
	{
		obj = ptr.obj;
		ptr.obj = nullptr;
	}
	L_autoPtr(L_autoPtr<T>& ptr) :obj(ptr.release())
	{
		
	}

	//不标准的复制赋值（转移内部指针控制权）
	L_autoPtr& operator=(L_autoPtr<T>& ptr)
	{
		delete obj;
		obj = ptr.obj;
		ptr.obj = nullptr;
		return *this;
	}
	L_autoPtr& operator=(L_autoPtr<T>& ptr)
	{
		obj = ptr.release();
		return *this;
	}

	//reset 释放之前，获得新的指针
	void reset(T*newPtr)
	{
		delete obj;
		obj = newPtr;
	}

	//release()释放控制权，返回指针
	T* release()
	{
		auto temp = obj;
		obj = nullptr;
		return temp;
	}
	//operator*()模拟指针访问方法
	T& operator*()
	{
		return *obj;
	}
	//operator->()模拟指针箭头式访问方法

	T* operator->()
	{
		return obj;
	}
	//get() 获得指针指向的指针
	T * get()
	{
		return obj;
	}
};