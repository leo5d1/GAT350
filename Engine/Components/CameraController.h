#pragma once 
#include "Framework/Component.h" 

namespace c14
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

			void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		float speed = 0;
	};
}