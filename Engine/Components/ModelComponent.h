#pragma once
#include "RenderComponent.h"

namespace c14
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelComponent)

		virtual void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Draw(Renderer& renderer) override;


	public:
		std::shared_ptr<Model> m_model;


	};
}