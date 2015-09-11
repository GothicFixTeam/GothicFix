#ifndef _COMMON_ARRAY_
#define _COMMON_ARRAY_

namespace COMMON
{

#define COMMON_DEFAULT_GRANULARITY 16

template<class type, int granularity = COMMON_DEFAULT_GRANULARITY, typename sizetype = uInt, typename sorttype = int>
class Array : public Object
{
public:
	typedef int (*CompFunc)(const type& obj1, const type& obj2, Object* arg);
	typedef void (*MoveFunc)(type* to, const type* from, sizetype size);
	typedef void (*ZeroFunc)(type* first, sizetype count);

public:
	static void DefaultCopier(type* to, const type* from, sizetype size)
	{
		memcpy(to, from, size * sizeof(type));
	}

	static void DefaultMover(type* to, const type* from, sizetype size)
	{
		memmove(to, from, size * sizeof(type));
	}

	static void DefaultZeroMaker(type* first, sizetype count)
	{
		memset(first, 0, sizeof(type) * count);
	}

protected:
	type*		Data;
	sizetype	Amount;
	sizetype	Allocated;
	sizetype	Granularity;

	MoveFunc Copier;
	MoveFunc Mover;
	ZeroFunc ZeroMaker;

	CompFunc			Comparator;
	TunablePtr<Object>	ComparatorArg;

public:
	void SetGranularity(sizetype value)
	{
		Granularity = value;
	}

	void SetMover(MoveFunc copier, MoveFunc mover)
	{
		Copier = copier;
		Mover = mover;
	}

	void SetComparator(CompFunc comparator)
	{
		Comparator = comparator;
		ComparatorArg = NULL;
	}

	void SetComparator(CompFunc comparator, TunablePtr<Object>& arg)
	{
		Comparator = comparator;
		ComparatorArg = arg;
	}

	// Size returns assigned size, excluding not assigned
	sizetype Size(void) const
	{
		return Amount;
	}

	// Reserved returns total allocated size, including not assigned
	sizetype Reserved(void) const
	{
		return Allocated;
	}

	/* Reserve only allocates space for elements, not changing size of array,
	argument is number of elements to add */
	void Reserve(sizetype count)
	{
		if(count && (Amount + count > Allocated))
		{
			if(Granularity > 1)
			{
				sizetype Granules = (Amount + count) / Granularity;
				if((Amount + count) % Granularity)
					++Granules;
				Allocated = Granules * Granularity;
			}
			else
				Allocated = Amount + count;

			type* OldData = Data;
			Data = new type[Allocated];
			if(Amount)
				Copier(Data, OldData, Amount);

			if(OldData)
				delete[] OldData;
		}
	}

	/* Allocate allocates space for elements and change size of array,
	argument is number of elements to add */
	sizetype Allocate(sizetype count)
	{
		sizetype Result = Amount;
		Reserve(count);
		Amount += count;
		return Result; 
	}

	/* SetSize change size of array and allocates space for elements, if new size is greater,
	argument is new size */
	sizetype SetSize(sizetype size)
	{
		if(size > Amount)
			return Allocate(size - Amount);
		else
			Amount = size;
		return Amount;
	}

	/* SetMaxSize change size of array only to greater value and allocates space for elements,
	argument is new size */
	sizetype SetMaxSize(sizetype size)
	{
		if(size > Amount)
			return Allocate(size - Amount);
		return Amount;
	}

	void Clear(void)
	{
		if(Data)
		{
			delete[] Data;
			Data = NULL;
			Amount = 0;
			Allocated = 0;
		}
	}

	void ResetSize(void)
	{
		Amount = 0;
	}

	void Compact(void)
	{
		if(!Amount)
			Clear();
		else
			if(Amount < Allocated)
		{
			type* OldData = Data;
			Data = new type[Amount];
			for(sizetype i = 0; i < Amount; i++)
				Data[i] = OldData[i];
			delete[] OldData;
			Allocated = Amount;
		}
	}

	type& Add(const type& object)
	{
		Reserve(1);
		Data[Amount] = object;
		return Data[Amount++];
	}

	type& Add(void)
	{
		Reserve(1);
		return Data[Amount++];
	}

	type& Add(const type* objects, sizetype size)
	{
		Reserve(size);
		Copier(&Data[Amount], objects, size);
		sizetype OldAmount = Amount;
		Amount += size;
		return Data[OldAmount];
	}

	type& Add(const Array<type, granularity, sizetype>& objects)
	{
		return Add(objects.Data, objects.Amount);
	}

	type& Insert(sizetype index, const type& object)
	{
		if(index > Amount)
			index = Amount;

		Reserve(1);
		if(index < Amount)
			Mover(&Data[index + 1], &Data[index], Amount - index);
		Data[index] = object;
		Amount++;

		return Data[index];
	}

	type& Insert(sizetype index)
	{
		if(index > Amount)
			index = Amount;

		Reserve(1);
		if(index < Amount)
		{
			Mover(&Data[index + 1], &Data[index], Amount - index);
			ZeroMaker(&Data[index], 1);
		}
		Amount++;

		return Data[index];
	}

	type& Insert(sizetype index, const type* objects, sizetype size)
	{
		if(index > Amount)
			index = Amount;

		Reserve(size);
		if(index < Amount)
			Mover(&Data[index + size], &Data[index], Amount - index);
		Copier(&Data[index], objects, size);
		Amount += size;

		return Data[index];
	}

	type& Insert(const Array<type, granularity, sizetype>& objects)
	{
		return Insert(objects.Data, objects.Amount);
	}

	type& Insert(sizetype index, const Array<type, granularity, sizetype>& objects)
	{
		return Insert(index, objects.Data, objects.Amount);
	}

	bool Erase(const type& object)
	{
		for(sizetype i = 0; i < Amount; i++)
		{
			if(Data[i] == object)
			{
				if(i < Amount - 1)
					Mover(&Data[i], &Data[i + 1], Amount - i - 1);
				ZeroMaker(&Data[--Amount], 1);
				return true;
			}
		}
		return false;
	}

	bool EraseIndex(const sizetype index)
	{
		if(index < Amount)
		{
			if(index < Amount - 1)
				Mover(&Data[index], &Data[index + 1], Amount - index - 1);
			ZeroMaker(&Data[--Amount], 1);
			return true;
		}
		return false;
	}

	bool EraseRange(const sizetype from, const sizetype to)
	{
		if((from < Amount) && (to < Amount))
		{
			if(to < Amount - 1)
				Mover(&Data[from], &Data[to + 1], Amount - to - 1);
			sizetype Count = to - from + 1;
			Amount -= Count; 
			ZeroMaker(&Data[Amount], Count);
			return true;
		}
		return false;
	}

	/* WARNING: This functions are intended only for fast array management, 
	   do not use it for sorted arrays, remember, that this function don't 
	   delete removed element */
	bool Remove(const type& object) 
	{
		for(sizetype i = 0; i < Amount; i++)
		{
			if(Data[i] == object)
			{
				if(i < Amount - 1)
					Data[i] = Data[Amount - 1];
				Amount--;
				ZeroMaker(&Data[Amount], 1);
				return true;
			}
		}
		return false;
	}

	bool RemoveIndex(const sizetype index) 
	{
		if(index < Amount)
		{
			if(index < Amount - 1)
				Data[index] = Data[Amount - 1];
			Amount--;
			ZeroMaker(&Data[Amount], 1);
			return true;
		}
		return false;
	}

	bool SwapIndex(const sizetype first, const sizetype second)
	{
		if((first < Amount) && (second < Amount) 
			&& (first != second))
		{
			type Temp = Data[first];
			Data[first] = Data[second];
			Data[second] = Temp;
			return true;
		}
		return false;
	}

	bool Exists(const type& object)
	{
		for(sizetype i = 0; i < Amount; i++)
		{
			if(Data[i] == object)
				return true;
		}
		return false;
	}

	type& operator [] (int i) const
	{
		return Data[i];
	}

	type& GetElement(sizetype i) const
	{
		return Data[i];
	}

	type& GetLast(void) const
	{
		return Data[Amount - 1];
	}

	type* GetData(void) const
	{
		return Data;
	}

	operator type* (void) const
	{
		return Data;
	}

	operator void* (void) const
	{
		return Data;
	}

	const Array<type, granularity, sizetype>& operator = (const Array<type, granularity, sizetype>& objects)
	{
		Clear();
		Add(objects);
		return *this;
	}

	/* Ascending sorting, from minimum to maximum. */
	void Sort(void)
	{
		if(Amount > 1)
			SortSubSet(0, Amount - 1);
	}

	void SortSubSet(sorttype first, sorttype last)
	{
		if(Comparator)
		{
			sorttype i = first;
			sorttype j = last;

			type Obj = Data[(first + last)/2];

			while(i <= j)
			{
				while(Comparator(Data[i], Obj, ComparatorArg) < 0)
					i++;
				while(Comparator(Data[j], Obj, ComparatorArg) > 0)
					j--;

				if(i <= j)
				{
					type Save = Data[i];

					Data[i++] = Data[j];
					Data[j--] = Save;
				}
			}

			if(first < j)
				SortSubSet(first, j);
			if(i < last)
				SortSubSet(i, last);
		}
	}

	bool Compare(const Array<type, granularity, sizetype>& objects) const
	{
		if(&objects == this)
			return true;
		if(objects.Amount != Amount)
			return false;
		if(Amount)
			return (memcmp(Data, objects.Data, sizeof(type) * Amount) == 0);
		return true;
	}

	bool operator == (const Array<type, granularity, sizetype>& objects) const 
	{
		return Compare(objects);
	}

	bool operator != (const Array<type, granularity, sizetype>& objects) const 
	{
		return !Compare(objects);
	}

public:
	Array(sizetype startsize = 0)
	{
		Data = NULL;
		Amount = 0;
		Allocated = 0;
		Granularity = granularity;

		Copier = DefaultCopier;
		Mover = DefaultMover;
		Comparator = NULL;
		ZeroMaker = DefaultZeroMaker;

		if(startsize)
			Reserve(startsize);
	}

	Array(const Array<type, granularity, sizetype>& objects)
	{
		Data = NULL;
		Amount = 0;
		Allocated = 0;
		Granularity = granularity;

		Copier = DefaultCopier;
		Mover = DefaultMover;
		Comparator = NULL;
		ZeroMaker = DefaultZeroMaker;

		Add(objects);
	}

	virtual ~Array(void)
	{
		Clear();
	}
};

typedef Array<uInt> uIntArray;
typedef Array<float> FloatArray;

template<class type, int granularity = COMMON_DEFAULT_GRANULARITY, typename sizetype = uInt>
class ObjectArray : public Array<type, granularity, sizetype>
{
public:
	static int DefaultComparator(const type& obj1, const type& obj2, Object* arg)
	{
		if(obj1 == obj2)
			return 0;
		if(obj1 > obj2)
			return 1;
		return -1;
	}

	static void DefaultCopier(type* to, const type* from, sizetype size)
	{
		for(sizetype i = 0; i < size; i++)
			to[i] = from[i];
	}

	static void DefaultMover(type* to, const type* from, sizetype size)
	{
		if(from > to) // For delete
		{
			for(sizetype i = 0; i < size; i++)
				to[i] = from[i];
		}
		else // For insert
		{
			for(sizetype i = size; i > 0; i--)
				to[i - 1] = from[i - 1];
		}
	}

	static void DefaultZeroMaker(type* first, sizetype count)
	{
		while(count--)
			first[count] = type();
	}

public:
	inline const ObjectArray<type, granularity, sizetype>& operator = (const ObjectArray<type, granularity, sizetype>& objects)
	{
		Clear();
		Add(objects);
		return *this;
	}

	bool Compare(const Array<type, granularity, sizetype>& objects) const { return false; };
	bool operator == (const Array<type, granularity, sizetype>& objects) const { return false; };
	bool operator != (const Array<type, granularity, sizetype>& objects) const { return false; };

	bool Compare(const ObjectArray<type, granularity, sizetype>& objects) const
	{
		if(&objects == this)
			return true;
		if(objects.Amount != Amount)
			return false;
		for(sizetype i = 0; i < Amount; i++)
		{
			if(Comparator(Data[i], objects.Data[i]))
				return false;
		}
		return true;
	}

	bool operator == (const ObjectArray<type, granularity, sizetype>& objects) const 
	{
		return Compare(objects);
	}

	bool operator != (const ObjectArray<type, granularity, sizetype>& objects) const 
	{
		return !Compare(objects);
	}

public:
	ObjectArray(sizetype startsize = 0) : Array(startsize)
	{
		Copier = DefaultCopier;
		Mover = DefaultMover;
		ZeroMaker = DefaultZeroMaker;
	}

	ObjectArray(const ObjectArray<type, granularity, sizetype>& objects) : Array(0)
	{
		Copier = DefaultCopier;
		Mover = DefaultMover;
		ZeroMaker = DefaultZeroMaker;

		Add(objects);
	}

	virtual ~ObjectArray(void)
	{
	}
};

}

#endif