#pragma once
#include "Resource.h"
#include <map>
#include <string>
#include <memory>
#include <cstdarg>
#include <vector>

namespace c14
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		void Initialize();
		void Shutdown();

		template <typename T, typename ... TArgs>
		std::shared_ptr<T> Get(const std::string& name, TArgs... args);

		template <typename T>
		std::vector<std::shared_ptr<T>> Get();

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;
	};

	template<typename T, typename ... TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& name, TArgs... args)
	{
		if (m_resources.find(name) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T> (m_resources[name]);
		}
		else
		{
			// not found, create reasource and enter into resources
			std::shared_ptr<T> resource = std::make_shared<T>();
			resource->Create(name, args...);
			m_resources[name] = resource;

			return resource;
		}
	}

	template <typename T>
	inline std::vector<std::shared_ptr<T>> ResourceManager::Get()
	{
		std::vector<std::shared_ptr<T>> result;

		for (auto& resource : m_resources)
		{
			// get the value of the map (first = key, second = value)
			// the value is a shared_ptr, get() the raw pointer and try to cast to type T*
			if (dynamic_cast<T*>(resource.second.get()))
			{
				// if it is of type T, add the shared pointer to the vector
				result.push_back(std::dynamic_pointer_cast<T>(resource.second));
			}
		}

		return result;
	}
}