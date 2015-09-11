#ifndef _COMMON_OBJECT_
#define _COMMON_OBJECT_

namespace COMMON
{

class Object
{
private:
	int		Reference;
	void*	UserData;
#ifdef _DEBUG
	bool	Debug;
#endif

public:
	virtual void*	GetUserData(void) const { return UserData; };
	virtual void	SetUserData(void* data) { UserData = data; };

protected:
	Object(void)
	{
		Reference = 0;
		UserData = NULL;
#ifdef _DEBUG
		Debug = false;
#endif
	}

public:
	virtual void Save(void)
	{
#ifdef _DEBUG
		if(Debug)
			printf("Save\n");
#endif
		++Reference;
	}

	virtual void Release(void)
	{
#ifdef _DEBUG
		if(Debug)
			printf("Release\n");
#endif
		if(--Reference <= 0)
			delete this;
	}

	virtual void ReleaseNoDelete(void)
	{
		--Reference;
	}

	virtual int GetRefCount(void) const
	{
		return Reference;
	}

	virtual void SetDebug(bool value)
	{
#ifdef _DEBUG
		Debug = value;
#endif
	}

	virtual Object* Clone(void) const
	{
		return (Object*)this;
	}

	virtual ~Object(void)
	{
	}

public:
	inline bool operator == (const Object& data) const
	{
		return false;
	}

	inline bool operator > (const Object& data) const
	{
		return false;
	}

};

template<class type>
class AutoPtr
{
private:
	type* Object;

public:
	AutoPtr(void)
	{
		Object = NULL;
	}

	AutoPtr(type* object)
	{
		Object = object;

		if(Object)
			Object->Save();
	}

	AutoPtr(const AutoPtr<type>& object)
	{
		Object = object.Object;

		if(Object)
			Object->Save();
	}

	AutoPtr<type>& operator = (type* object)
	{
		if(Object != object)
		{
			if(Object)
				Object->Release();

			Object = object;
			if(Object)
				Object->Save();
		}

		return *this;
	}

	AutoPtr<type>& operator = (const AutoPtr<type>& object)
	{
		if(Object != object.Object)
		{
			if(Object)
				Object->Release();

			Object = object.Object;
			if(Object)
				Object->Save();
		}

		return *this;
	}

	operator type* (void) const
	{
		return Object;
	}

	template <class type2> operator type2* (void) const
	{
		type2* pObj = dynamic_cast<type2*>(Object);
#if _DEBUG
		assert(pObj != NULL);
#endif
		return pObj;
	}

	template <class type2> operator AutoPtr<type2>(void) const
	{
		return AutoPtr<type2>((type2*)Object);
	}

	type* operator -> (void) const
	{
		return Object;
	}

	type& operator * (void) const
	{
		return *Object;
	}

	bool operator == (type* object) const
	{
		return Object == object;
	}

	bool operator != (type* object) const
	{
		return Object != object;
	}

	bool operator == (const AutoPtr<type>& object) const
	{
		return Object == object.Object;
	}

	bool operator != (const AutoPtr<type>& object) const
	{
		return Object != object.Object;
	}

	bool operator > (const AutoPtr<type>& object) const
	{
		return Object > object.Object;
	}

	type* Detach()
	{
		type* pRes = Object;

		if(Object)
		{
			Object->ReleaseNoDelete();
			Object = NULL;
		}

		return pRes;
	}

	~AutoPtr()
	{
		if(Object)
			Object->Release();
		Object = NULL;
	}
};

template<class type>
class TunablePtr
{
private:
	type*	Object;
	bool	Auto;

public:
	TunablePtr(void)
	{
		Object = NULL;
		Auto = true;
	}

	TunablePtr(type* object, bool isauto = true)
	{
		Object = object;
		Auto = isauto;

		if(Object && Auto)
			Object->Save();
	}

	TunablePtr(const AutoPtr<type>& object)
	{
		Object = object.Object;
		Auto = true;

		if(Object && Auto)
			Object->Save();
	}

	TunablePtr(const TunablePtr<type>& object)
	{
		Object = object.Object;
		Auto = object.Auto;

		if(Object && Auto)
			Object->Save();
	}

	TunablePtr<type>& operator = (type* object)
	{
		if(Object != object)
		{
			if(Object && Auto)
				Object->Release();

			Object = object;

			if(Object && Auto)
				Object->Save();
		}

		return *this;
	}

	TunablePtr<type>& operator = (const AutoPtr<type>& object)
	{
		if(Object != object.Object)
		{
			if(Object && Auto)
				Object->Release();

			Object = object.Object;
			if(Object && Auto)
				Object->Save();
		}

		return *this;
	}

	TunablePtr<type>& operator = (const TunablePtr<type>& object)
	{
		if(Object != object.Object)
		{
			if(Object && Auto)
				Object->Release();

			Object = object.Object;
			Auto = object.Auto;

			if(Object && Auto)
				Object->Save();
		}

		return *this;
	}

	operator type* (void) const
	{
		return Object;
	}

	template <class type2> operator type2* (void) const
	{
		type2* pObj = dynamic_cast<type2*>(Object);
#if _DEBUG
		assert(pObj != NULL);
#endif
		return pObj;
	}

	template <class type2> operator AutoPtr<type2>(void) const
	{
		return AutoPtr<type2>((type2*)Object);
	}

	template <class type2> operator TunablePtr<type2>(void) const
	{
		return TunablePtr<type2>((type2*)Object);
	}

	type* operator -> (void) const
	{
		return Object;
	}

	type& operator * (void) const
	{
		return *Object;
	}

	bool operator == (type* object) const
	{
		return Object == object;
	}

	bool operator != (type* object) const
	{
		return Object != object;
	}

	bool operator == (const AutoPtr<type>& object) const
	{
		return Object == object.Object;
	}

	bool operator == (const TunablePtr<type>& object) const
	{
		return Object == object.Object;
	}

	bool operator != (const AutoPtr<type>& object) const
	{
		return Object != object.Object;
	}

	bool operator != (const TunablePtr<type>& object) const
	{
		return Object != object.Object;
	}

	bool operator > (const AutoPtr<type>& object) const
	{
		return Object > object.Object;
	}

	bool operator > (const TunablePtr<type>& object) const
	{
		return Object > object.Object;
	}

	type* Detach()
	{
		type* pRes = Object;

		if(Object && Auto)
			Object->ReleaseNoDelete();
		Object = NULL;

		return pRes;
	}

	void SetAuto(bool value)
	{
		Auto = value;
	}

	bool GetAuto(void) const
	{
		return Auto;
	}

	~TunablePtr()
	{
		if(Object && Auto)
			Object->Release();
		Object = NULL;
	}
};

typedef AutoPtr<Object> ObjectPtr;

}

#endif