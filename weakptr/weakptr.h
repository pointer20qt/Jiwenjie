#pragma once

namespace lan
{
	//ģ�廯�����Խ�����������
	//std::   
	template<class T>
	class L_autoPtr{
		T* obj = nullptr;
	public:
		//���췽������ֵһ��ָ��
		L_autoPtr(T* ptr) :obj(ptr){
		}

		L_autoPtr() = default;

		//�����������ͷ�ָ��
		~L_autoPtr(){
			delete obj;
		}

		//����׼�ĸ��ƹ���(ת���ڲ�ָ�����Ȩ)
		L_autoPtr(L_autoPtr<T>& ptr) :obj(ptr.release()){

		}

		//����׼�ĸ��Ƹ�ֵ(ת���ڲ�ָ�����Ȩ)
		L_autoPtr& operator=(L_autoPtr<T>& ptr){
			obj = ptr.release();
			return *this;
		}

		//reset �ͷ�֮ǰ�ģ�����µ�ָ��
		void reset(T* newPtr = nullptr){
			delete obj;
			obj = newPtr;
		}

		//release()  �ͷſ���Ȩ������ָ��
		T* release(){
			auto temP = obj;
			obj = nullptr;
			return temP;
		}

		//operator*() ģ��ָ����ʷ���
		T& operator*(){
			return *obj;
		}

		//operator->() ģ��ָ���ͷʽ���ʷ���
		T* operator->(){
			return obj;
		}

		//get()  ���ָ��ָ���ָ��
		T* get(){
			return obj;
		}

	};

	template<class T> class L_uniquePtr{
		T* obj = nullptr;
	public:
		//���췽������ֵһ��ָ��
		L_uniquePtr(T* ptr) :obj(ptr){
		}

		L_uniquePtr(const T&) = delete;
		L_uniquePtr() = default;

		//�����������ͷ�ָ��
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

		//reset �ͷ�֮ǰ�ģ�����µ�ָ��
		void reset(T* newPtr = nullptr){
			delete obj;
			obj = newPtr;
		}

		//release()  �ͷſ���Ȩ������ָ��
		T* release(){
			auto temP = obj;
			obj = nullptr;
			return temP;
		}

		//operator*() ģ��ָ����ʷ���
		T& operator*(){
			return *obj;
		}

		//operator->() ģ��ָ���ͷʽ���ʷ���
		T* operator->(){
			return obj;
		}

		//get()  ���ָ��ָ���ָ��
		T* get(){
			return obj;
		}
	};
	//��Դ������
	template<class T>
	class Ref{
		//��ǰ��Դ����
		int r_count = 0;
		//��ǰ������ָ�����
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

		L_sharedPtr(Ref<T>* newRef){
			ref = newRef;
			if (ref)
			{
				ref->increase();
			}
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

	template<class T>class L_weakPtr;
	template<class T>
	class L_weakPtr
	{
		friend class L_weakPtr<T>;
		Ref<T>* ref = nullptr;
	public:
		//�޲ι���
		L_weakPtr() = default;
		//����һ��shared_ptr����
		L_weakPtr(L_sharedPtr<T>&other):ref(other.ref)
		{
			if (ref)
			{
				ref.increase_w();
			}
			return *this;
		}
		//��������
		L_weakPtr(const L_weakPtr<T>& other) :ref(other.ref)
		{
			if (ref)
			{
				ref.increase_w();
			}
		}
		//�ƶ�����
		L_weakPtr(L_weakPtr<T>&&other)
		{
			swap(ref, other.ref);
		}
		//������ֵ
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

		//�ƶ���ֵ
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

		//�ж��Ƿ��Ѿ�ɾ��
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
			//��ref�����T������һ�𴴽���
			//����һ��ref������new T����
			L_sharedPtr<T> t(new T(a...));
			return t;
		}
}