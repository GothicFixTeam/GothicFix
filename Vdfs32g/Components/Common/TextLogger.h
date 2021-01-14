#ifndef _TEXT_LOGGER_
#define _TEXT_LOGGER_

#include <fstream>
#include <string>
#include <vector>

namespace COMMON
{
	class TextLogger
	{
	private:
		static bool initialized;
		static const char* const filename;
		static const char* const delimeter;
		static const int maxEntries;
		static const int persistentEntries;
		static std::fstream file;

		static void WriteDate();
		static std::vector<std::fstream::pos_type> GetEntriesPos();
		static void Delete(const std::fstream::pos_type& from, const int& length);
		static void Init();

	public:
		template <class T>
		static void Log(const T& message);
	
		static void Log(const std::wstring& message);
		static std::ostream& Log();
	};

	template <class T>
	void TextLogger::Log(const T& message)
	{
		Log() << message << std::endl;
	}
}

#endif