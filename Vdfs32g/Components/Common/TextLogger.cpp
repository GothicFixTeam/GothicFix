#include "PreCompiled.h"
#include "TextLogger.h"
#include <ctime>
#include <iomanip>

namespace COMMON
{
	bool TextLogger::initialized = false;
	const char* const TextLogger::filename = "sp.log";
	const char* const TextLogger::delimeter = "============================================================";
	const int TextLogger::maxEntries = 7;
	const int TextLogger::persistentEntries = 2;
	std::fstream TextLogger::file;

	void TextLogger::WriteDate()
	{
		std::time_t gTime = std::time(NULL);
		std::tm* now = std::localtime(&gTime);
		
		file << "Game Started: " << std::setfill('0') << std::setw(2) << now->tm_mday << "/";
		file << std::setfill('0') << std::setw(2) << now->tm_mon + 1 << "/";
		file << now->tm_year + 1900 << " - ";
		file << std::setfill('0') << std::setw(2) << now->tm_hour << ":";
		file << std::setfill('0') << std::setw(2) << now->tm_min << ":";
		file << std::setfill('0') << std::setw(2) << now->tm_sec << std::endl;

		file << std::string(strlen(delimeter), '-') << std::endl;
	}

	std::vector<std::fstream::pos_type> TextLogger::GetEntriesPos()
	{
		file.open(filename, std::ios::in);
		std::vector<std::fstream::pos_type> positions;
		char buffer[4096];

		for (std::fstream::pos_type prevPos = 0; file.getline(buffer, 4096); prevPos = file.tellg())
		{
			if (strcmp(delimeter, buffer) != 0)
			{
				continue;
			}

			positions.push_back(prevPos);
		}

		file.close();
		file.clear();
		return positions;
	}

	void TextLogger::Delete(const std::fstream::pos_type& from, const int& length)
	{
		file.open(filename, std::ios::in | std::ios::binary);

		file.seekg(0, std::ios::end);
		int fileSize = (int)file.tellg();

		file.seekg(0);
		char* buffer = new char[fileSize - length];

		file.read(buffer, (int)from);
		int currSize = int(file.gcount());

		file.seekg((int)from + length);
		file.read(buffer + currSize, fileSize - file.tellg());
		currSize += int(file.gcount());
		file.close();
		file.clear();

		file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
		file.write(buffer, currSize);
		file.close();
		file.clear();

		delete[] buffer;
	}

	void TextLogger::Init()
	{
		if (initialized)
		{
			return;
		}

		std::vector<std::fstream::pos_type> positions = GetEntriesPos();
		
		if (positions.size() >= maxEntries)
		{
			std::fstream::pos_type from = positions[persistentEntries];
			std::fstream::pos_type toExclusive = positions[persistentEntries + (int)positions.size() - maxEntries + 1];
			Delete(from, (int)toExclusive - (int)from);
		}

		file.open(filename, std::ios::out | std::ios::app);
		file << std::endl << delimeter << std::endl;
		WriteDate();

		initialized = true;
	}

	void TextLogger::Log(const std::wstring& message)
	{
		Init();
		std::string cMessage(message.begin(), message.end());
		file << cMessage << std::endl;
	}

	std::ostream& TextLogger::Log()
	{
		Init();
		return file;
	}
}