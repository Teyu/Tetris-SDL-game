#ifndef TSINGLETON
#define TSINGLETON

template <class T>
class TSingleton
{
protected:
	static T *m_pSingleton;

public:
	virtual ~TSingleton() {}
	inline static T* Get()
	{
		if (!m_pSingleton) //Existiert schon eine Instanz?
		{
			m_pSingleton = new T;
		}
		return (m_pSingleton);
	}
	static void Del()
	{
		if (m_pSingleton)
		{
			delete (m_pSingleton);
			m_pSingleton = NULL;
		}
	}
};

//statische Variablen m�ssen au�erhalb erzeugt werden!
template <class T>
T* TSingleton<T>::m_pSingleton = 0;

#endif