#pragma once
#include "Actor.h"
#include <list>
#include <memory>

namespace c14
{
	// forward declaration
	class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game{ game } {}
		Scene(const Scene& other) {}
		~Scene() = default;

		CLASS_DECLARATION(Scene)

		void Initialize() override;
		void Update() override;
		void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		
		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActorFromName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorFromTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		Game* m_game;
		std::list<std::unique_ptr<Actor>> m_actors;

	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}
		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorFromName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (name == actor->GetName())
			{
				return dynamic_cast<T*>(actor.get());
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorFromTag(const std::string& tag)
	{
		std::vector<T*> result;

		for (auto& actor : m_actors)
		{
			if (tag == actor->GetTag())
			{
				T* TagActor = dynamic_cast<T*>(actor.get());
				if (TagActor)
				{
					result.push_back(TagActor);
				}
			}
		}

		return std::vector<T*>();
	}
}