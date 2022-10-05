#pragma once
#include <string>

namespace c14
{
	void SetFilePath(const std::string& pathname);

	std::string GetFilePath();
	
	bool FileExists(const std::string& pathname);
	bool GetFileSize(const std::string& pathname, size_t& size);
	bool ReadFile(const std::string& pathname, std::string& buffer);
}