#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template < class T >
class Singleton
{
private:
	static T *instance;

protected:
	Singleton() {}
public:
	static T* getInstance()
	{
		if (!instance)
			instance = new T;

		return instance;
	}

	static void releaseInstance()
	{
		if (instance)
		{
			delete instance;
			instance = NULL;
		}
	}
private:
	Singleton(Singleton &const);
	Singleton& operator=(Singleton const&);
};

template < class T >
T *Singleton<T>::instance = nullptr;

#endif