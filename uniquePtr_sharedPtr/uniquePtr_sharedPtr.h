#pragma once

//模板化，可以接收任类型
template<class T> class L_uniquePtr{
	T* obj = nullptr;
public:
	L_uniquePtr(T* ptr) :obj(ptr){
	}
	L_uniquePtr(const T&) = delete;
	L_uniquePtr() = default;
	~L_uniquePtr(){
		delete obj;
	}
	L_uniquePtr& operator=(const L_autoPtr<T>&) = delete;
	L_uniquePtr(L_autoPtr<T>&& ptr) :obj(ptr.release()){

	}
	L_uniquePtr& operator=(L_autoPtr<T>&& ptr){
		obj = ptr.release();
		return *this;
	}
	void reset(T* newPtr = nullptr){
		delete obj;
		obj = newPtr;
	}
	T* release(){
		auto temP = obj;
		obj = nullptr;
		return temP;
	}
	T& operator*(){
		return *obj;
	}
	T* operator->(){
		return obj;
	}
	T* get(){
		return obj;
	}
};
//资源计数类
template<class T>
class Ref{
	//当前资源计数
	int r_count = 0;
	T* object = nullptr;
public:
	Ref(T* target) :object(target){
		++r_count;
	}
	inline void increase(){
		r_count++;
	}
	inline void reduce(){
		r_count--;
		if (r_count == 0){
			delete object;
			delete this;
		}
	}
	//获得对对象
	T* get(){
		return object;
	}
	int getCount(){
		return r_count;
	}
};
//shared智能指针需要的方法
template<class T> class L_sharedPtr{
	Ref<T>* ref = nullptr;
public:
	L_sharedPtr() = default;
	~L_sharedPtr(){
		if (ref){
			ref->reduce();
		}
	}

	//传递指针构造
	L_sharedPtr(T* newP){
		ref = new Ref<T>(newP);
	}

	//拷贝构造
	L_sharedPtr(const L_sharedPtr& other){
		ref = other.ref;
		if (ref){
			ref->increase();
		}
	}

	//移动构造
	L_sharedPtr(L_sharedPtr&& other){
		swap(ref, other.ref);
	}

	//拷贝赋值
	L_sharedPtr& operator=(const L_sharedPtr& other){
		if (ref){
			ref->reduce();
		}
		ref = other.ref;
		if (ref){
			ref->increase();
		}
		return *this;
	}

	//移动赋值
	L_sharedPtr& operator=(L_sharedPtr&& other){
		if (ref){
			ref->reduce();
		}
		ref = other.ref;
		other.ref = nullptr;
		return *this;
	}

	//交换
	void swap(L_sharedPtr& other){
		swap(ref, other.ref);
	}
	//reset(T*)替换对象
	void reset(T* target = nullptr){
		if (ref){
			ref->reduce();
		}
		if (target != nullptr){
			ref = new Ref<T>(target);
		}
		else{
			ref = nullptr;
		}
	}

	//reset() 销毁对象
	void reset()
	{
		if (ref)
		{
			ref->reduce();
		}
		ref = nullptr;
	}
	//operator*()
	T& operator*(){
		if (ref){
			return *ref->get();
		}
		else{
			return *(T*)nullptr;
		}
	}

	//operator->()
	T* operator->(){
		if (ref){
			return ref->get();
		}
		else{
			return (T*)nullptr;
		}
	}

	//get()获得裸指针
	T* get(){
		if (ref){
			return ref->get();
		}
		else{
			return (T*)nullptr;
		}
	}
	//use_count() 获得引用计数
	int use_count(){
		if (ref){
			return ref->getCount();
		}
		else{
			return 0;
		}
	}

	//unique() 判断当前是否唯一  use_count() == 1
	bool unique(){
		if (ref){
			return ref->getCount() == 1;
		}
		else{
			return false;
		}
	}
	//判断当前只能指针是否和对象关联
	operator bool(){
		return ref != nullptr;
	}
};