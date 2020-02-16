#pragma once

//ģ�廯�����Խ���������
template<class T>
class L_autoPtr
{
	T* obj = nullptr;
public:
	//���췽������ֵһ��ָ��
	L_autoPtr(T* ptr) :obj(ptr)
	{
	}
	//�����������ͷ�ָ��
	~L_autoPtr()
	{
		delete obj;
	}
	//����׼�ĸ��ƹ��죨ת���ڲ�ָ�����Ȩ��
	L_autoPtr(L_autoPtr<T>& ptr)
	{
		obj = ptr.obj;
		ptr.obj = nullptr;
	}
	L_autoPtr(L_autoPtr<T>& ptr) :obj(ptr.release())
	{
		
	}

	//����׼�ĸ��Ƹ�ֵ��ת���ڲ�ָ�����Ȩ��
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

	//reset �ͷ�֮ǰ������µ�ָ��
	void reset(T*newPtr)
	{
		delete obj;
		obj = newPtr;
	}

	//release()�ͷſ���Ȩ������ָ��
	T* release()
	{
		auto temp = obj;
		obj = nullptr;
		return temp;
	}
	//operator*()ģ��ָ����ʷ���
	T& operator*()
	{
		return *obj;
	}
	//operator->()ģ��ָ���ͷʽ���ʷ���

	T* operator->()
	{
		return obj;
	}
	//get() ���ָ��ָ���ָ��
	T * get()
	{
		return obj;
	}
};