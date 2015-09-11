#ifndef _COMMON_HASH_TABLE_
#define _COMMON_HASH_TABLE_

namespace COMMON
{

enum HashType
{
HASH_CRC8 = 0x100,
HASH_CRC16 = 0x10000
};

template <typename type, int hashsize = HASH_CRC8>
class HashTable : public Object
{
public:
	class Container
	{
	private:
		HashTable<type>* Array;
		bool	Named;
		uChar*	ElementName;
		uChar*	ElementNameToPass;
		uInt	ElementNameLen;

	public:
		Container(HashTable<type>* table, const char* name, uInt length)
		{
			Array = table;
			Named = true;
			ElementName = (uChar*)name;
			ElementNameToPass = ElementName;
			ElementNameLen = length;
		}

		Container(HashTable<type>* table, const uInt num)
		{
			Array = table;
			Named = false;
			(*(uInt*)&ElementName) = num;
			ElementNameToPass = (uChar*)&ElementName;
			ElementNameLen = sizeof(uInt);
		}

		Container(HashTable<type>* table, const void* ptr)
		{
			Array = table;
			Named = false;
			ElementName = (uChar*)ptr;
			ElementNameToPass = (uChar*)&ElementName;
			ElementNameLen = sizeof(void*);
		}

		Container(Container& Cont)
		{
			Array = Cont.Array;
			Named = Cont.Named;
			ElementName = Cont.ElementName;
			if(Cont.ElementNameToPass == Cont.ElementName)
				ElementNameToPass = ElementName;
			else
				ElementNameToPass = (uChar*)&ElementName;
			ElementNameLen = Cont.ElementNameLen;
		}

		void operator ~ (void)
		{
			(Array->*(Array->DelFunc))(ElementNameToPass, ElementNameLen);
		}

		const type& operator = (const type& data)
		{
			(Array->*(Array->SetFunc))(data, ElementNameToPass, ElementNameLen);
			return data;
		}

		type operator = (const Container& Cont)
		{
			type data = (type)Cont;
			(*this) = data;
			return data;
		}

		operator type (void) const
		{
			if(type* Tmp = (Array->*(Array->GetFunc))(ElementNameToPass, ElementNameLen))
				return *Tmp;
			return type(0);
		}

		bool Exists(void) const
		{
			if(type* Tmp = (Array->*(Array->GetFunc))(ElementNameToPass, ElementNameLen))
				return true;
			return false;
		}

		operator type* (void) const
		{
			return (Array->*(Array->GetFunc))(ElementNameToPass, ElementNameLen);
		}

		~Container(void) {};
	};

private:
	class NodeEntry : public Object
	{
	public:
		type Data;
		Array<uChar, 1> Name;

	public:
		NodeEntry(void)
		{
			memset(&Data, 0, sizeof(type));
		}

		NodeEntry(int)
		{
			memset(&Data, 0, sizeof(type));
		}

		NodeEntry(NodeEntry& Other)
		{
			Data = Other.Data;
			Name = Other.Name;
		}

		void Set(const type& data, const uChar* name, uInt len)
		{
			Data = data;
			Name.Add(name, len);
		}

		bool CheckName(const uChar* name, uInt len) const
		{
			return ((Name.Size() == len) && (!memcmp(Name.GetData(), name, len)));
		}

		~NodeEntry(void) { };

	};

private:
	ObjectArray<NodeEntry, 1>* Data;

public:
	void (HashTable<type, hashsize>::*SetFunc)(const type& data, const uChar* name, uInt len);
	type* (HashTable<type, hashsize>::*GetFunc)(const uChar* name, uInt len) const;
	void (HashTable<type, hashsize>::*DelFunc)(const uChar* name, uInt len);

private:
	void Set8(const type& data, const uChar* name, uInt len)
	{
		uChar Hash = Crc8(name, len);
		switch(Data[Hash].Size())
		{
		case 0:
			Data[Hash].Add().Set(data, name, len);
			break;
		case 1:
			{
				if(Data[Hash][0].CheckName(name, len))
				{
					Data[Hash][0].Data = data;
					return;
				}
				Data[Hash].Add().Set(data, name, len);
			}
			break;
		default:
			for(uInt i = 0; i < Data[Hash].Size(); i++)
			{
				if(Data[Hash][i].CheckName(name, len))
				{
					Data[Hash][i].Data = data;
					return;
				}
			}
			Data[Hash].Add().Set(data, name, len);
			break;
		};
	}

	void Set16(const type& data, const uChar* name, uInt len)
	{
		uShort Hash = Crc16(name, len);
		switch(Data[Hash].Size())
		{
		case 0:
			Data[Hash].Add().Set(data, name, len);
			break;
		case 1:
			{
				if(Data[Hash][0].CheckName(name, len))
				{
					Data[Hash][0].Data = data;
					return;
				}
				Data[Hash].Add().Set(data, name, len);
			}
			break;
		default:
			for(uInt i = 0; i < Data[Hash].Size(); i++)
			{
				if(Data[Hash][i].CheckName(name, len))
				{
					Data[Hash][i].Data = data;
					return;
				}
			}
			Data[Hash].Add().Set(data, name, len);
			break;
		};
	}

	type* Get8(const uChar* name, uInt len) const
	{
		uChar Hash = Crc8(name, len);
		switch(Data[Hash].Size())
		{
		case 0:
			break;
		case 1:
			{
				if(Data[Hash][0].CheckName(name, len))
					return &Data[Hash][0].Data;
			}
			break;
		default:
			for(uInt i = 0; i < Data[Hash].Size(); i++)
			{
				if(Data[Hash][i].CheckName(name, len))
					return &Data[Hash][i].Data;
			}
			break;
		}
		return NULL;
	}

	type* Get16(const uChar* name, uInt len) const
	{
		uShort Hash = Crc16(name, len);
		switch(Data[Hash].Size())
		{
		case 0:
			break;
		case 1:
			{
				if(Data[Hash][0].CheckName(name, len))
					return &Data[Hash][0].Data;
			}
			break;
		default:
			for(uInt i = 0; i < Data[Hash].Size(); i++)
			{
				if(Data[Hash][i].CheckName(name, len))
					return &Data[Hash][i].Data;
			}
			break;
		}
		return NULL;
	}

	void Del8(const uChar* name, uInt len)
	{
		uChar Hash = Crc8(name, len);
		switch(Data[Hash].Size())
		{
		case 0:
			break;
		case 1:
			if(Data[Hash][0].CheckName(name, len))
				Data[Hash].EraseIndex(0);
			break;
		default:
			for(uInt i = 0; i < Data[Hash].Size(); i++)
			{
				if(Data[Hash][i].CheckName(name, len))
					Data[Hash].EraseIndex(i);
			}
			break;
		}
	}

	void Del16(const uChar* name, uInt len)
	{
		uShort Hash = Crc16(name, len);
		switch(Data[Hash].Size())
		{
		case 0:
			break;
		case 1:
			if(Data[Hash][0].CheckName(name, len))
				Data[Hash].EraseIndex(0);
			break;
		default:
			for(uInt i = 0; i < Data[Hash].Size(); i++)
			{
				if(Data[Hash][i].CheckName(name, len))
					Data[Hash].EraseIndex(i);
			}
			break;
		}
	}

public:
	HashTable(void)
	{
		assert((hashsize == HASH_CRC16) || (hashsize == HASH_CRC8));
		switch(hashsize)
		{
		case HASH_CRC16:
			{
				Data = new ObjectArray<NodeEntry, 1>[hashsize];
				SetFunc = &HashTable<type, hashsize>::Set16;
				GetFunc = &HashTable<type, hashsize>::Get16;
				DelFunc = &HashTable<type, hashsize>::Del16;
			}
			break;
		case HASH_CRC8:
			{
				Data = new ObjectArray<NodeEntry, 1>[hashsize];
				SetFunc = &HashTable<type, hashsize>::Set8;
				GetFunc = &HashTable<type, hashsize>::Get8;
				DelFunc = &HashTable<type, hashsize>::Del8;
			}
			break;
		default:
			break;
		}
	}

	Container operator [] (const wchar_t* name) const
	{
		Container Cont((HashTable<type> *)this, (const char*)name, (uInt)wcslen(name) * sizeof(wchar_t));
		return Cont;
	}

	Container operator [] (const char* name) const
	{
		Container Cont((HashTable<type> *)this, name, (uInt)strlen(name));
		return Cont;
	}

	Container operator [] (const int num) const
	{
		Container Cont((HashTable<type> *)this, (uInt)num);
		return Cont;
	}

	Container operator [] (const void* ptr) const
	{
		Container Cont((HashTable<type> *)this, ptr);
		return Cont;
	}

	void Clear(void)
	{
		delete[] Data;
		Data = new ObjectArray<NodeEntry, 1>[hashsize];
	}

	virtual ~HashTable(void)
	{
		delete[] Data;
	}
};

}

#endif