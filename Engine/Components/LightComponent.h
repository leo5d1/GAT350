#pragma once
#include "Framework/Component.h"

namespace c14
{
	enum Type {
		Point,
		Directional,
		Spot
	};

	class LightComponent : public Component
	{
	public:
		CLASS_DECLARATION(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 color{ 0 };
		Type type = Type::Point;

		float cutoff = 45.0f;
		float exponent = 50.0f;
	};
}