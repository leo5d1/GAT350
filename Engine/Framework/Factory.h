#pragma once
#include "Singleton.h"
#include "Core/Logger.h"
#include <memory>
#include <map>

namespace c14
{
	class GameObject;

	class CreatorBase
	{
	public:
		virtual ~CreatorBase() = default;

		virtual std::unique_ptr<GameObject> Create() = 0;
	};

	template <typename T>
	class Creator : public CreatorBase
	{
	public:
		virtual std::unique_ptr<GameObject> Create() override
		{
			return std::make_unique<T>();
		}
	};

	template <typename T>
	class PrefabCreator : public CreatorBase
	{
	public:
		~PrefabCreator() = default;

		PrefabCreator(std::unique_ptr<T> instance) : m_instance{ std::move(instance) } {}

		virtual std::unique_ptr<GameObject> Create() override
		{
			return m_instance->Clone();
		}

	private:
		std::unique_ptr<T> m_instance;
	};

	class Factory : public Singleton<Factory>
	{
	public:
		void Shutdown() { m_registry.clear(); }

		template <typename T>
		void Register(const std::string& key);

		template <typename T>
		void RegisterPrefab(const std::string& key, std::unique_ptr<T> instance);

		template <typename T>
		std::unique_ptr<T> Create(const std::string& key);

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

	template <typename T>
	inline void Factory::Register(const std::string& key)
	{
		m_registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
	inline void Factory::RegisterPrefab(const std::string& key, std::unique_ptr<T> instance)
	{
		m_registry[key] = std::make_unique<PrefabCreator<T>>(std::move(instance));
	}

	template <typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key)
	{
		auto iter = m_registry.find(key);
		if (iter != m_registry.end())
		{
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}

		LOG("error could not find key %s", key.c_str());

		return std::unique_ptr<T>();
	}
}