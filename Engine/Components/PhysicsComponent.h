#pragma once
#include "Framework/Component.h"
#include "Math/Vector2.h"

namespace c14
{
	class Actor;

	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		CLASS_DECLARATION(PhysicsComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void ApplyForce(const Vector2& force) { acceleration += force; }

	public:
		Vector2 velocity;
		Vector2 acceleration;

		float damping = 1;
	};
}