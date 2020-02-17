#pragma once

//ģ�廯�����Խ���������
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
//��Դ������
template<class T>
class Ref{
	//��ǰ��Դ����
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
	//��öԶ���
	T* get(){
		return object;
	}
	int getCount(){
		return r_count;
	}
};
//shared����ָ����Ҫ�ķ���
template<class T> class L_sharedPtr{
	Ref<T>* ref = nullptr;
public:
	L_sharedPtr() = default;
	~L_sharedPtr(){
		if (ref){
			ref->reduce();
		}
	}

	//����ָ�빹��
	L_sharedPtr(T* newP){
		ref = new Ref<T>(newP);
	}

	//��������
	L_sharedPtr(const L_sharedPtr& other){
		ref = other.ref;
		if (ref){
			ref->increase();
		}
	}

	//�ƶ�����
	L_sharedPtr(L_sharedPtr&& other){
		swap(ref, other.ref);
	}

	//������ֵ
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

	//�ƶ���ֵ
	L_sharedPtr& operator=(L_sharedPtr&& other){
		if (ref){
			ref->reduce();
		}
		ref = other.ref;
		other.ref = nullptr;
		return *this;
	}

	//����
	void swap(L_sharedPtr& other){
		swap(ref, other.ref);
	}
	//reset(T*)�滻����
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

	//reset() ���ٶ���
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

	//get()�����ָ��
	T* get(){
		if (ref){
			return ref->get();
		}
		else{
			return (T*)nullptr;
		}
	}
	//use_count() ������ü���
	int use_count(){
		if (ref){
			return ref->getCount();
		}
		else{
			return 0;
		}
	}

	//unique() �жϵ�ǰ�Ƿ�Ψһ  use_count() == 1
	bool unique(){
		if (ref){
			return ref->getCount() == 1;
		}
		else{
			return false;
		}
	}
	//�жϵ�ǰֻ��ָ���Ƿ�Ͷ������
	operator bool(){
		return ref != nullptr;
	}
};