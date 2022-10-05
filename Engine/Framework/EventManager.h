#pragma once
#include "Event.h"
#include <map>
#include <list>

namespace c14
{
	class EventManager
	{
	public:
		struct Observer
		{
			GameObject* reciever = nullptr;
			Event::functionPtr function;
		};

	public:
		void Initialize();
		void Shutdown();
		void Update();

		void Subscribe(const std::string& name, Event::functionPtr function, GameObject* reciever = nullptr);
		void Unsubscribe(const std::string& name, GameObject* reciever);

		void Notify(const Event& event);

	private:
		std::map<std::string, std::list<Observer>> m_events;
	};
}