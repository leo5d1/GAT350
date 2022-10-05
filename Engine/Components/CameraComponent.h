#pragma once
#include "Framework/Component.h" 
#include "Math/Matrix3x3.h" 

namespace c14
{
	class CameraComponent : public Component
	{
	public:
		CLASS_DECLARATION(CameraComponent)

			virtual void Initialize() override;
		virtual void Update() override;

		const Matrix3x3& GetView() { return m_view; }

		void SetViewport(const Vector2& size);
		const Matrix3x3& GetViewport() { return m_viewport; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Vector2 viewport_size;

		Matrix3x3 m_view;
		Matrix3x3 m_viewport;
	};
}