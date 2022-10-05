#include "CharacterComponent.h"
#include "Engine.h"

namespace c14
{
	CharacterComponent::~CharacterComponent()
	{
		g_eventManager.Unsubscribe("EVENT_DAMAGE", m_owner);
	}

	void CharacterComponent::Initialize()
	{
		// bind events
		g_eventManager.Subscribe("EVENT_DAMAGE", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);

		// bind collision events
		auto component = m_owner->GetComponent<CollisionComponent>();
		if (component)
		{
			component->SetCollisionEnter(std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1));
			component->SetCollisionExit(std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1));
		}
	}

	bool CharacterComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CharacterComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, health);
		READ_DATA(value, damage);
		READ_DATA(value, speed);

		return true;
	}
}