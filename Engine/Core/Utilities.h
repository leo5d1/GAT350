#pragma once
#include <string>

namespace c14
{
	std::string ToLower(const std::string& str);
	std::string ToUpper(const std::string& str);
	bool CompareIgnoreCase(const std::string& str1, const std::string& str2);
}