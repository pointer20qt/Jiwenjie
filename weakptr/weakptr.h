#pragma once

namespace lan
{
	//模板化，可以接受任意类型
	//std::   
	template<class T>
	class L_autoPtr{
		T* obj = nullptr;
	public:
		//构造方法，赋值一个指针
		L_autoPtr(T* ptr) :obj(ptr){
		}

		L_autoPtr() = default;

		//析构方法，释放指针
		~L_autoPtr(){
			delete obj;
		}

		//不标准的复制构造(转移内部指针控制权)
		L_autoPtr(L_autoPtr<T>& ptr) :obj(ptr.release()){

		}

		//不标准的复制赋值(转移内部指针控制权)
		L_autoPtr& operator=(L_autoPtr<T>& ptr){
			obj = ptr.release();
			return *this;
		}

		//reset 释放之前的，获得新的指针
		void reset(T* newPtr = nullptr){
			delete obj;
			obj = newPtr;
		}

		//release()  释放控制权，返回指针
		T* release(){
			auto temP = obj;
			obj = nullptr;
			return temP;
		}

		//operator*() 模拟指针访问方法
		T& operator*(){
			return *obj;
		}

		//operator->() 模拟指针箭头式访问方法
		T* operator->(){
			return obj;
		}

		//get()  获得指针指向的指针
		T* get(){
			return obj;
		}

	};

	template<class T> class L_uniquePtr{
		T* obj = nullptr;
	public:
		//构造方法，赋值一个指针
		L_uniquePtr(T* ptr) :obj(ptr){
		}

		L_uniquePtr(const T&) = delete;
		L_uniquePtr() = default;

		//析构方法，释放指针
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

		//reset 释放之前的，获得新的指针
		void reset(T* newPtr = nullptr){
			delete obj;
			obj = newPtr;
		}

		//release()  释放控制权，返回指针
		T* release(){
			auto temP = obj;
			obj = nullptr;
			return temP;
		}

		//operator*() 模拟指针访问方法
		T& operator*(){
			return *obj;
		}

		//operator->() 模拟指针箭头式访问方法
		T* operator->(){
			return obj;
		}

		//get()  获得指针指向的指针
		T* get(){
			return obj;
		}
	};
	//资源计数类
	template<class T>
	class Ref{
		//当前资源计数
		int r_count = 0;
		//当前弱引用指针计数
		int w_count = 0;
		T* object = nullptr;
	public:
		Ref(T* target) :object(target){
			++r_count;
		}
		inline void increase(){
			r_count++;
		}
		inline void increase_w(){
			w_count++;
		}
		inline void reduce()
		{
			r_count--;
			if (r_count == 0)
			{
				delete object;
				object = nullptr;
				if (w_count == 0)
				{
					delete this;
				}
			}
		}
		inline void reduce_w()
		{
			w_count--;
			if (w_count == 0 && r_count == 0)
			{
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

		L_sharedPtr(Ref<T>* newRef){
			ref = newRef;
			if (ref)
			{
				ref->increase();
			}
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

	template<class T>class L_weakPtr;
	template<class T>
	class L_weakPtr
	{
		friend class L_weakPtr<T>;
		Ref<T>* ref = nullptr;
	public:
		//无参构造
		L_weakPtr() = default;
		//传递一个shared_ptr构造
		L_weakPtr(L_sharedPtr<T>&other):ref(other.ref)
		{
			if (ref)
			{
				ref.increase_w();
			}
			return *this;
		}
		//拷贝构造
		L_weakPtr(const L_weakPtr<T>& other) :ref(other.ref)
		{
			if (ref)
			{
				ref.increase_w();
			}
		}
		//移动构造
		L_weakPtr(L_weakPtr<T>&&other)
		{
			swap(ref, other.ref);
		}
		//拷贝赋值
		L_weakPtr<T>&operator=(const L_weakPtr<T>&other)
		{
			if (ref)
			{
				ref->reduce_w();
			}
			ref = other.ref;
			if (ref)
			{
				ref->increase_w();
			}
			return *this;
		}

		//移动赋值
		L_weakPtr<T>&operator=(L_weakPtr<T>&&other)
		{
			if (ref)
			{
				ref->reduce_w();
			}
			ref = other.ref;
			other.ref = nullptr;
			return *this;
		}
		int use_count()
		{
			if (ref)
				return ref->getCount();
			else
			{
				return 0;
			}
		}

		//判断是否已经删除
		bool expired()
		{
			if (ref)

			{
				return ref->getCount() > 0;
			}
			else
			{
				return 0;
			}
		}

		L_sharedPtr<T> lock()
		{
			L_sharedPtr<T>tem(ref);
			return tem;
		}
		void swap(L_weakPtr<T>&other)
		{
			swap(ref, other.ref);
		}
		void reset()
		{
			ref->reduce_w();
			ref = nullptr;
		}
	};

	template<class T, class ...args>
	L_sharedPtr<T>
		make_L_shared(args... a){
			//将ref对象和T对象在一起创建。
			//创建一次ref对象，在new T对象
			L_sharedPtr<T> t(new T(a...));
			return t;
		}
}