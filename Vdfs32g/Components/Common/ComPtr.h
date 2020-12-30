#ifndef _ARE_COM_PTR_
#define _ARE_COM_PTR_

template<class type>
class ComPtr
{
protected:
	type* Ptr;

public:
	type* Set(type* ptr)
	{
		Ptr = ptr;
		return ptr;
	}

	type* Get(void)
	{
		return Ptr;
	}

	type** GetAddressOf(void)
	{
		return &Ptr;
	}

	template<class type2>
	type2* As(ComPtr<type2>* as)
	{
		if(SUCCEEDED(Ptr->QueryInterface(__uuidof(**as->GetAddressOf()), (void**)as->GetAddressOf())))
			(*as)->AddRef();
		return *as->GetAddressOf();
	}

	type* operator = (type* other)
	{
		if(Ptr)
			Ptr->Release();
		if(Ptr = other)
			Ptr->AddRef();
		return other;
	}

	const ComPtr<type>& operator = (ComPtr<type>& other)
	{
		if(Ptr)
			Ptr->Release();
		if(Ptr = other.Get())
			Ptr->AddRef();
		return other;
	}

	template<class type2>
	const ComPtr<type2>& operator = (ComPtr<type2>& other)
	{
		if(Ptr)
			Ptr->Release();
		if(Ptr = other.Get())
			Ptr->AddRef();
		return other;
	}

	operator type* (void) const
	{
		return Ptr;
	}

	type* operator -> (void) const
	{
		return Ptr;
	}

	operator bool(void) const
	{
		return (Ptr != NULL);
	}

public:
	ComPtr(void)
	{
		Ptr = NULL;
	}

	ComPtr(type* ptr)
	{
		Ptr = ptr;
	}

	~ComPtr(void)
	{
		if(Ptr)
		{
			Ptr->Release();
			Ptr = NULL;
		}
	}
};

#endif