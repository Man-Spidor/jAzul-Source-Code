#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>

class StringConverter
{
private:
	StringConverter() = default;
	StringConverter(const StringConverter&) = delete;
	StringConverter(StringConverter&&) = delete;
	StringConverter& operator=(const StringConverter&) = delete;
	StringConverter& operator=(StringConverter&&) = delete;
	~StringConverter() = default;

public:
	static std::wstring StringToWide(std::string str);
};

#endif