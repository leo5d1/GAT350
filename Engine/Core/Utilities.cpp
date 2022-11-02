#include "Utilities.h" 
#include <algorithm> 

namespace c14
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) { return std::toupper(c); });

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](const char& c1, const char& c2) {
			return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
			}));
	}
}