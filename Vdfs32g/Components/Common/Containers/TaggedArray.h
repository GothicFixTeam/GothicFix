#ifndef _COMMON_TAGGED_ARRAY_
#define _COMMON_TAGGED_ARRAY_

namespace COMMON
{

template<class type, class tagtype, int granularity = COMMON_DEFAULT_GRANULARITY>
class TaggedArray : public Object
{
public:
	class NodeEntry : public Object
	{
	public:
		tagtype Tag;
		type	Value;

	public:
		NodeEntry(void) {};
		virtual ~NodeEntry(void) {};
	};

public:
	typedef int (*CompFunc)(const NodeEntry& obj1, const NodeEntry& obj2, Object* arg);

private:
	ObjectArray<NodeEntry, granularity>	SubArray;
	bool Deduplicate;
	mutable type TempValue;

public:
	// Size returns assigned size, excluding not assigned
	uInt Size(void) const
	{
		return SubArray.Size();
	}

	// Reserved returns total allocated size, including not assigned
	uInt Reserved(void) const
	{
		return SubArray.Reserved();
	}

	void Reserve(uInt count)
	{
		SubArray.Reserve(count);
	}

	uInt Allocate(uInt count)
	{
		return SubArray.Allocate(count);
	}

	uInt SetSize(uInt size)
	{
		return SubArray.SetSize(size);
	}

	void Clear(void)
	{
		SubArray.Clear();
	}

	void ResetSize(void)
	{
		SubArray.ResetSize();
	}

	void Compact(void)
	{
		SubArray.Compact();
	}

	type& Add(const tagtype& tag)
	{
		if(Deduplicate)
		{
			for(uInt i = 0; i < SubArray.Size(); i++)
			{
				if(SubArray[i].Tag == tag)
				{
					return SubArray[i].Value;
				}
			}
		}

		NodeEntry& Entry = SubArray.Add();
		Entry.Tag = tag;
		return Entry.Value;
	}

	type& Add(const tagtype& tag, const type& value)
	{
		if(Deduplicate)
		{
			for(uInt i = 0; i < SubArray.Size(); i++)
			{
				if(SubArray[i].Tag == tag)
				{
					return SubArray[i].Value;
				}
			}
		}

		NodeEntry& Entry = SubArray.Add();
		Entry.Tag = tag;
		Entry.Value = value;
		return Entry.Value;
	}

	type& Replace(const tagtype& tag, const type& value)
	{
		if(Deduplicate)
		{
			for(uInt i = 0; i < SubArray.Size(); i++)
			{
				if(SubArray[i].Tag == tag)
				{
					return (SubArray[i].Value = value);
				}
			}
		}

		NodeEntry& Entry = SubArray.Add();
		Entry.Tag = tag;
		Entry.Value = value;
		return Entry.Value;
	}

	void AddArray(const TaggedArray<type, tagtype, granularity>& objects)
	{
		if(Deduplicate)
		{
			for(uInt i = 0; i < objects.SubArray.Size(); i++)
				Add(objects.SubArray[i].Tag, objects.SubArray[i].Value);
		}
		else
			SubArray.Add(objects.SubArray);
	}

	bool EraseByTag(const tagtype& tag)
	{
		for(uInt i = 0; i < SubArray.Size(); i++)
		{
			if(SubArray[i].Tag == tag)
			{
				SubArray.EraseIndex(i);
				return true;
			}
		}
		return false;
	}

	bool EraseByValue(const type& value)
	{
		for(uInt i = 0; i < SubArray.Size(); i++)
		{
			if(SubArray[i].Value == value)
			{
				return SubArray.EraseIndex(i);
			}
		}
		return false;
	}

	bool EraseIndex(const uInt index)
	{
		return SubArray.EraseIndex(index);
	}

	type& GetElement(int i) const
	{
		return SubArray[i].Value;
	}

	type& GetElement(uInt i) const
	{
		return SubArray[i].Value;
	}

	type& GetLast(void) const
	{
		if(SubArray.Size())
			return SubArray[SubArray.Size() - 1].Value;
		return TempValue;
	}

	type& operator [] (int i) const
	{
		return SubArray[i].Value;
	}

	type& GetElement(const tagtype& tag) const
	{
		for(uInt i = 0; i < SubArray.Size(); i++)
		{
			if(SubArray[i].Tag == tag)
			{
				return SubArray[i].Value;
			}
		}
		return TempValue;
	}

	inline type& operator [] (const tagtype& tag) const
	{
		for(uInt i = 0; i < SubArray.Size(); i++)
		{
			if(SubArray[i].Tag == tag)
			{
				return SubArray[i].Value;
			}
		}
		return TempValue;
	}

	tagtype& GetTag(int i) const
	{
		return SubArray[i].Tag;
	}

	tagtype& GetTag(uInt i) const
	{
		return SubArray[i].Tag;
	}

	bool TagExist(const tagtype& tag) const
	{
		for(uInt i = 0; i < SubArray.Size(); i++)
		{
			if(SubArray[i].Tag == tag)
			{
				return true;
			}
		}
		return false;
	}

	const TaggedArray<type, tagtype, granularity>& operator = (const TaggedArray<type, tagtype, granularity>& objects)
	{
		Clear();
		AddArray(objects);
		return *this;
	}

	void Sort(void)
	{
		SubArray.Sort();
	}

	void SortSubSet(uInt first, uInt last)
	{
		SubArray.SortSubSet(first, last);
	}

	bool GetDeduplicate(void) const
	{
		return Deduplicate;
	}

	void SetDeduplicate(bool deduplicate)
	{
		Deduplicate = deduplicate;
	}

	// If concrete invalid result required, call this function
	void SetInvalidResult(const type& value)
	{
		TempValue = value;
	}

public:
	static int DefaultComparator(const NodeEntry& obj1, const NodeEntry& obj2, Object* arg)
	{
		if(obj1.Tag == obj2.Tag)
			return 0;
		if(obj1.Tag > obj2.Tag)
			return 1;
		return -1;
	}

	void SetComparator(CompFunc comparator, TunablePtr<Object>& arg)
	{
		SubArray.SetComparator(comparator, arg);
	}

	void SetComparator(CompFunc comparator)
	{
		SubArray.SetComparator(comparator);
	}

public:
	TaggedArray(bool deduplicate = false, uInt startsize = 0)
	{
		Deduplicate = deduplicate;
		SubArray.SetComparator(DefaultComparator);
		if(startsize)
			SubArray.Reserve(startsize);
	}

	TaggedArray(const TaggedArray<type, tagtype, granularity>& objects, bool deduplicate = false)
	{
		Deduplicate = deduplicate;
		SubArray.SetComparator(DefaultComparator);
		AddArray(objects);
	}

	virtual ~TaggedArray(void)
	{
		Clear();
	}
};

}

#endif