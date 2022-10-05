#pragma once
#include <string>

namespace c14
{
	class Resource
	{
	public:
		virtual bool Create(const std::string name, ...) = 0;
	};
}